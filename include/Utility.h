/* Contains developpement utility functions */

#pragma once

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