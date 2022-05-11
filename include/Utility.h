/* Contains developpement utility functions */

#pragma once

#include "Struct.h"

#include <stdio.h>

/* Print Matrix mat of order N in terminal*/
void printMatrix(int *mat, int N);

/* Print all the arc of queue in terminal */
void printArcQueue(Arc * queue);

/* Print the node visited in order in terminal */
void printNodeQueue(Arc * queue);

/* Return a copy of queue */
Arc * copyQueue(Arc * queue);

/* Change all the element of lign l and col c to -1 */
void maskLignCol(int * adj, int N, int l, int c);