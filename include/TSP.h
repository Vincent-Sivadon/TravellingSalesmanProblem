#pragma once

#include "Struct.h"

/* @param initialAdj : the adjacency matrix of the first problem
 * @param N : the number of nodes */
void TSP(Problem * p);

/* Evaluate the inferior bound of a given problem */
void bound(Problem * p);