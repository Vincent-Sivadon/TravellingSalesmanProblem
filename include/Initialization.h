/* Contains adjacency matrix data structure related features */

#pragma once

/* Construct adjacency matrix for a N complete graph
 * with random valued arcs between 1 and 20 */
int* randomInitialization(int N);

/* Initialize matrix adjacency from list of edges */
void fileInitialization(const char *filename, int ** adj, int * N);