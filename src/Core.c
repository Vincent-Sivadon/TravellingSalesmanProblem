#include "Core.h"
#include "Utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limits.h"

/* For every line of the adjacency matrix,
 * We consider the min cost for leaving the node corresponding to that line
 * and subtract that amount to all elements of this lign
 * Returns the sum of all the minimum exit cost */
int minCostForLeaving(int * adj, int N)
{
    // Sum of all lign minimums (for problem bounds)
    int sum_of_all_mins = 0;

    // Run through every lines
    for (int i=0 ; i<N ; i++)
    {
        // Store the minimum value of that lign
        int min = INT_MAX;
        
        // Run through every element of that lign
        // Searching for the minimum value
        for (int j=0 ; j<N ; j++)
            if (adj[i*N + j] < min && adj[i*N + j] != -1)
                min = adj[i*N + j];

        // Skip masked ligns
        if (min == INT_MAX) continue;
        
        // Accumulate those minimums
        sum_of_all_mins += min;

        // Run a second time through every element of that lign
        // Subtracting min to these elements
        for (int j=0 ; j<N ; j++)
            if (adj[i*N + j] != -1)
                adj[i*N + j] -= min;
    }

    return sum_of_all_mins;
}

/* For every column of the adjacency matrix,
 * We consider the min cost for entering the node corresponding to that column
 * and subtract that amount to all elements of this column
 * Returns the sum of all the minimum entering cost */
int minCostForEntering(int * adj, int N)
{
    // Sum of all lign minimums (for problem bounds)
    int sum_of_all_mins = 0;

    // Run through every column
    for (int j=0 ; j<N ; j++)
    {
        // Store the minimum value of that column
        int min = INT_MAX;
        
        // Run through every element of that column
        // Searching for the minimum value
        for (int i=0 ; i<N ; i++)
            if (adj[i*N + j] < min && adj[i*N + j] != -1)
                min = adj[i*N + j];

        // Skip masked Columns
        if (min == INT_MAX) continue;
        
        // Accumulate those minimums
        sum_of_all_mins += min;

        // Run a second time through every element of that column
        // Subtracting min to these elements
        for (int i=0 ; i<N ; i++)
            if (adj[i*N + j] != -1)
                adj[i*N + j] -= min;
    }

    return sum_of_all_mins;
}

/* Evaluate the inferior bound of a given problem
 * Will modify the adjacency matrix */
void bound(Problem * p)
{
    int bound = 0;
    bound += minCostForLeaving(p->adj, p->N);
    bound += minCostForEntering(p->adj, p->N);

    p->bound = bound;
}

/* Given (k,l) representing an arc of adj, returns it's regret */
int getRegret(int * adj, int N, int k, int l)
{
    int minLign = INT_MAX;
    int minCol  = INT_MAX;
    
    // Run through the column
    for (int i=0 ; i<N ; i++)
        if (i!= k && adj[i*N + l] != -1 && adj[i*N + l] < minCol)
            minCol = adj[i*N + l];
    
    // Run through all the ligns
    for (int j=0 ; j<N ; j++)
        if (j!= l && adj[k*N + j] != -1 && adj[k*N + j] < minLign)
            minLign = adj[k*N + j];

    return minCol + minLign;
}

/* Returns the arc of max regret given a graph of size N represented by adj */
Arc * getArcOfMaxRegret(int * adj, int N)
{
    // Init
    Arc * arc_of_max_regret = newArc(-1, -1);

    int max_regret = -1;

    for (int i=0 ; i<N ; i++)
        for (int j=0 ; j<N ; j++)
            if (adj[i*N + j] == 0 && adj[i*N + j] != -1)
            {
                int regret = getRegret(adj, N, i, j);
                if (regret > max_regret) 
                {
                    arc_of_max_regret->i = i;
                    arc_of_max_regret->j = j;
                    max_regret = regret;
                }
            }

    return arc_of_max_regret;
}

void maskLignCol(int * adj, int N, int l, int c)
{
    for (int i=0 ; i<N ; i++)
        adj[i*N + c] = -1;
    for (int j=0 ; j<N ; j++)
        adj[l*N + j] = -1;
}

/* @param initialAdj : the adjacency matrix of the first problem
 * @param N : the number of nodes */
void TSP(Problem * p)
{
    if (p->queue_size >= p->N)
    {
        displayArcQueue(p->queue);
        return;
    }   

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
    addToQueue(&sub1->queue, arc_of_max_regret->i, arc_of_max_regret->j);
    sub1->queue_size = p->queue_size + 1;
    bound(sub1);

    if (sub1->bound <= sub2->bound)
        TSP(sub1);
    else
    {
        TSP(sub2);
    }
}