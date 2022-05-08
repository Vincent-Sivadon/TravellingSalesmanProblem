#include "TSP.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

void CoreTest()
{
    int * adj;
    int N;
    fileInitialization("../edges.txt", &adj, &N);

    Problem * p = newProblem();
    p->adj = adj;
    p->N = N;
    p->queue = newArc(-1,-1);
    p->queue_size = 0;
    bound(p);

    // Get arc of max regret
    Arc * arc_of_max_regret = getArcOfMaxRegret(p->adj, p->N);

    // Create sub problem 2
    Problem * sub2 = newProblem();
    sub2->adj = (int *) malloc(p->N*p->N * sizeof(int));
    memcpy(sub2->adj, p->adj, p->N*p->N * sizeof(int));
    sub2->N = p->N;
    sub2->adj[arc_of_max_regret->i * sub2->N + arc_of_max_regret->j] = -1;
    sub2->queue = p->queue;
    sub2->queue_size = p->queue_size;
    sub2->bound = p->bound + getRegret(p->adj, p->N, arc_of_max_regret->i, arc_of_max_regret->j);

    // Create sub problem 1
    Problem * sub1 = newProblem();
    sub1->adj = p->adj;
    sub1->N = p->N;
    maskLignCol(sub1->adj, sub1->N, arc_of_max_regret->i, arc_of_max_regret->j);
    sub1->queue = p->queue;
    sub1->queue_size++;
    addToQueue(&sub1->queue, arc_of_max_regret->i, arc_of_max_regret->j); 
    bound(sub1);
}

int main(int argc, char const *argv[])
{
    CoreTest();
    printf("Core test passed\n");

    return 0;
}
