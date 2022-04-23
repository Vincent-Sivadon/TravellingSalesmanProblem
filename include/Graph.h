/* Contains adjacency matrix data structure related features */

#pragma once

// Represent an edge between to vertices
typedef struct arc {
    int i;
    int j;
    int regret;
    int id;
    struct arc * next;
} Arc;

/* Construct adjacency matrix for a N complete graph
 * with random valued arcs between 1 and 20 */
int* randomInitialization(int N);

/* Initialize matrix adjacency from list of edges */
int* fileInitialization(const char *filename);

/* Remove the Arc in matrix mat of size N
 * by masking lign arc->i and col arc->j */
void reduce(int * mat, int N, Arc * arc);

/* Get minimum element of the k-th lign */
int minLign(int * mat, int N, int k);

/* Get minimum element of the k-th column */
int minCol(int * mat, int N, int k);