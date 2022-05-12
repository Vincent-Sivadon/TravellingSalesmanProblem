/* 2022 Vincent Sivadon <vincent.sivadon@ens.uvsq.fr> */

#pragma once

#include "Struct.h"

/* Given (k,l) representing an arc of adj, returns it's regret */
int getRegret(int * adj, int N, int k, int l);

/* Returns the arc of max regret given a graph of size N represented by adj */
Arc * getArcOfMaxRegret(Problem * p);

/* When there's only 2 arcs left
 * we must adapt the procedure a bit
 * mainly we can't bound sub1 or we'll
 * loose the last regret information */
int addLastArcs(Problem * p);