#pragma once

#include "Struct.h"

/* @param initialAdj : the adjacency matrix of the first problem
 * @param N : the number of nodes */
void TSP(Problem * p);

/* Evaluate the inferior bound of a given problem */
void bound(Problem * p);

/* Given (k,l) representing an arc of adj, returns it's regret */
int getRegret(int * adj, int N, int k, int l);
/* Returns the arc of max regret given a graph of size N represented by adj */
Arc * getArcOfMaxRegret(int * adj, int N);

void maskLignCol(int * adj, int N, int l, int c);