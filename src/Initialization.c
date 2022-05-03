/* Contains adjacency matrix data structure related features */

#include "Initialization.h"

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

typedef unsigned long long u64;

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

int numberOfNodes(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    int max_node = 0;
    int node_i, node_j;
    int arc_value;
    char dump[50];

    // Skip first line (do nothing with it)
    fscanf(fp, "%[^\n]\n", dump);

    // Read line by line
    while (fscanf(fp, "%d %d %d\n", &node_i, &node_j, &arc_value) != EOF)
    {
        if (node_i > max_node) max_node = node_i;
        if (node_j > max_node) max_node = node_j;
    }

    fclose(fp);
    
    return max_node;
}

/* Initialize matrix adjacency from list of edges */
void fileInitialization(const char *filename, int ** adj, int * N)
{
    // Variables
    FILE *fp;
    int node_i, node_j;
    int arc_value;
    char dump[50];
    *N = numberOfNodes(filename) + 1;
    int * mat = (int *)calloc((*N)*(*N), sizeof(int));

    // Open Data File
    fp = fopen(filename, "r");
    if (!fp) {
        printf("Can't read '%s'\n", filename);
        exit(1);
    }

    // Skip first line (do nothing with it)
    fscanf(fp, "%[^\n]\n", dump);

    // Read line by line
    while (fscanf(fp, "%d %d %d\n", &node_i, &node_j, &arc_value) != EOF)
        mat[node_i * (*N) + node_j] = arc_value;

    // Initialize to -1 the diagonal
    for (int i=0 ; i<(*N) ; i++)
        mat[i*(*N) + i] = -1;

    fclose(fp);

    *adj = mat;
}