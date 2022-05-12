/* 2022 Vincent Sivadon <vincent.sivadon@ens.uvsq.fr> */

#include "Initialization.h"

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

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

/* Get number of nodes from file */
int getNumberOfNodes(const char *filename)
{
    // Open Data File
    FILE * fp = fopen(filename, "r");
    if (!fp) {
        printf("Can't read '%s'\n", filename);
        exit(1);
    }

    char line[1024];
    int count = 0;
    while (fgets(line, 1024, fp))
        count++;
    

    fclose(fp);

    return count;
}

/* Initialize matrix adjacency from list of edges */
void fileInitialization(const char *filename, int ** adj, int * N)
{
    char line[1024];
    *N = getNumberOfNodes(filename);
    int * mat = malloc((*N)*(*N) * sizeof(int));
    int el;
    char *str;

    // Open Data File
    FILE * fp = fopen(filename, "r");
    if (!fp) {
        printf("Can't read '%s'\n", filename);
        exit(1);
    }

    int k = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s", line);
        str = strtok(line, " ");
        while (str != NULL)
        {
            if (str[0] == 'x') 
                mat[k] = -1;
            else
                mat[k] = atoi(str);
            str = strtok(NULL, ",");
            k++;
        }
    }

    for (int i = 0; i < *N; i++)
            assert(mat[i*(*N) + i] == -1);

    fclose(fp);

    *adj = mat;
}