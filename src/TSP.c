#include "TSP.h"
#include "Regret.h"
#include "Bound.h"
#include "Initialization.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

static int current_min = INT_MAX;
static Arc * best_queue;

/* Create Sub problem 1
 * @param arc : Arc of Max Regret of p */
Problem * createSub1(Problem *p, Arc * arc)
{
    // Declare
    Problem *sub1 = newProblem();
    int N = p->N;

    // Copy p adjacency matrix
    sub1->adj = (int *) malloc(N*N * sizeof(int));
    memcpy(sub1->adj, p->adj, N*N * sizeof(int));
    sub1->N = N;

    // Because we've already taken this arc
    // We can't enter again j, and exit again i
    maskLignCol(sub1->adj, sub1->N, arc->i, arc->j);

    // Arc Queue (p + arc)
    sub1->queue = copyQueue(p->queue);
    addToQueue(&sub1->queue, arc->i, arc->j);
    sub1->queue_size = p->queue_size + 1;

    // Reduction and evaluation
    bound(sub1);
    sub1->bound += p->bound;

    return sub1;
}

/* Create Sub problem 2
 * @param arc : Arc of Max Regret of p */
Problem * createSub2(Problem * p, Arc * arc)
{
    // Declare
    Problem * sub2 = newProblem();
    int N = p->N;

    // Copy p adjacency matrix
    sub2->adj = (int *) malloc(N*N * sizeof(int));
    memcpy(sub2->adj, p->adj, N*N * sizeof(int));
    sub2->N = N;

    // Mask the arc we won't take
    sub2->adj[arc->i * N + arc->j] = -1;

    // Arc queue (stay the same)
    sub2->queue = copyQueue(p->queue);
    sub2->queue_size = p->queue_size;

    // Evaluation
    bound(sub2);
    sub2->bound = p->bound + getRegret(p->adj, p->N, arc->i, arc->j);

    return sub2;
}

/* @param initialAdj : the adjacency matrix of the first problem
 * @param N : the number of nodes */
void TSPrecursiv(Problem * p)
{
    // If p is a leaf
    if (p->queue_size >= p->N-2)
    {
        // Add last arc
        if (addLastArcs(p) == 1)
            return;

        // If evaluation inferior than the current_min
        // Than it is the best one currently, and we print it
        if (p->bound < current_min)
        {
            current_min = p->bound;
            freeQueue(best_queue);
            best_queue = copyQueue(p->queue);
        }

        return;
    }

    Arc * arc_of_max_regret = getArcOfMaxRegret(p);
    if (arc_of_max_regret == NULL)
        return;

    Problem *sub1 = createSub1(p, arc_of_max_regret);
    Problem *sub2 = createSub2(p, arc_of_max_regret);

    if (sub1->bound < current_min)
        TSPrecursiv(sub1);
    if (sub2->bound < current_min)
        TSPrecursiv(sub2);

    freeProblem(sub1);
    freeProblem(sub2);
    free(arc_of_max_regret);
}

/* TSPrecursive init and call wrapper */
Arc * TSP(const char *filename)
{
    int * adj;
    int N;
    fileInitialization(filename, &adj, &N);

    Problem * p = newProblem();
    p->adj = adj;
    p->N = N;
    p->queue = newArc(-1,-1);
    p->queue_size = 0;
    bound(p);

    TSPrecursiv(p);

    freeProblem(p);

    return best_queue;
}