#include "TSP.h"

#include <stdlib.h>
#include <assert.h>

void maskTest()
{
    int * adj;
    int N;
    fileInitialization("../edges.txt", &adj, &N);
    maskLignCol(adj, N, 2, 1);

    assert(adj[2*N + 0] == -1);
    assert(adj[2*N + 1] == -1);
    assert(adj[2*N + 2] == -1);
    assert(adj[0*N + 1] == -1);
    assert(adj[1*N + 1] == -1);
    assert(adj[2*N + 1] == -1);

    assert(adj[N] != -1);
}

int main(int argc, char const *argv[])
{
    maskTest();
    printf("mask test passed\n");

    return 0;
}
