/* Contains developpement utility functions */

#pragma once

#include "Struct.h"

#include <stdio.h>

void displayMatrixTerminal(int *mat, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i * N + j]);
        printf("\n");
    }
}

void displayArcQueue(Arc * queue)
{
    while (queue != NULL)
    {
        printf("%d - %d\n", queue->i, queue->j);
        queue = queue->next;
    }
}
