#include "TSP.h"
#include "Struct.h"

#include <stdio.h>
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

/* Evaluate the inferior bound of a given problem */
void bound(Problem * p)
{
    int bound = 0;
    bound += minCostForLeaving(p->adj, p->N);
    bound += minCostForEntering(p->adj, p->N);

    p->bound = bound;
}


/* @param initialAdj : the adjacency matrix of the first problem
 * @param N : the number of nodes */
void TSP(int * initial_adj, int N)
{
    // Defines the initial problem
    Problem * p = newProblem();
    p->adj = initial_adj;
    p->N = N;
    
    // Bound
    bound(p);

    // Branch
}