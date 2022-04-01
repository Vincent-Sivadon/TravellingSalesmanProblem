/* */

#include "Graph.h"

#include <stdlib.h>
#include <unistd.h>

/* Construct adjacency matrix for a N complete graph
 * with random valued arcs between 1 and 20 */
int* randomInitialization(int N)
{
    int arcValue;

    // Random seed initialization
    srand(getpid());

    // Allocation
    int * mat = malloc(N * N * sizeof(int));

    // For every pair of nodes, init arc value
    for (int i=0 ; i<N ; i++)
        for (int j=0 ; j<N ; j++)
        {
            if (i==j)
                arcValue = -1;
            else 
                arcValue = 1 + rand() % 19;

            mat[i * N + j] = arcValue;
        }

    return mat;
}