/* Contains adjacency matrix data structure related features */

#include "Graph.h"

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
int* fileInitialization(const char *filename)
{
    // Variables
    FILE *fp;
    int node_i, node_j;
    int arc_value;
    char dump[50];
    int N = numberOfNodes(filename) + 1;
    int* adjacency_matrix = (int *)calloc(N*N, sizeof(int));

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
        adjacency_matrix[node_i * N + node_j] = arc_value;

    //fclose(fp);

    return adjacency_matrix;
}

/* Mask the k-th lign of the matrix mat of size N */
void maskLign(int* mat, int N, int k)
{
    for (int j=0 ; j<N ; j++)
        mat[k * N + j] = -1;
}

/* Mask the k-th column of the matrix mat of size N */
void maskCol(int* mat, int N, int k)
{
    for (int i=0 ; i<N ; i++)
        mat[i * N + k] = -1;
}

/* Remove the Arc in matrix mat of size N
 * by masking lign arc->i and col arc->j */
void reduce(int * mat, int N, Arc * arc)
{
    maskLign(mat, N, arc->i);
    maskCol(mat, N, arc->j);
}

/* Get minimum element of the k-th lign */
int minLign(int * mat, int N, int k)
{
    // Minimum arc value of that lign
    int min = INT_MAX;

    // Search for the minimum value of the column
    for (int j=0 ; j<N; j++)
        if (mat[k*N + j] < min && mat[k*N + j] != -1)
            min = mat[k*N + j];
    
    return min;
}

/* Get minimum element of the k-th column */
int minCol(int * mat, int N, int k)
{
    // Minimum arc value of that col
    int min = INT_MAX;

    // Search for the minimum value of the column
    for (int i=0 ; i<N; i++)
        if (mat[i*N + k] < min && mat[i*N + k] != -1)
            min = mat[i*N + k];
    
    return min;
}



