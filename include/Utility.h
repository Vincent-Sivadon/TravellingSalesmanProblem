/* Contains developpement utility functions */

#pragma once

#include "Graph.h"

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

void displayArcQueue(Arc * arc_queue_head)
{
    while (arc_queue_head != NULL)
    {
        printf("%d - %d\n", arc_queue_head->i, arc_queue_head->j);
        arc_queue_head = arc_queue_head->next;
    }
}