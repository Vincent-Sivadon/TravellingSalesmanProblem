#include "TSP.h"
#include "Utility.h"
#include "Initialization.h"

#include <stdlib.h>
#include <assert.h>

void boundTest()
{
    int * adj;
    int N;
    fileInitialization("../edges.txt", &adj, &N);

    Problem * p = newProblem();
    p->adj = adj;
    p->N = N;
    p->queue = newArc(-1,-1);
    p->queue_size = 0;
    bound(p);

    assert(adj[1] == 10);
    assert(adj[N + 4] == 0);
    assert(adj[2*N + 4] == 12);
    assert(adj[3*N + 1] == 5);
    assert(adj[4*N + 2] == 6);
}

int main(int argc, char const *argv[])
{
    boundTest();
    printf("bound test passed\n");

    return 0;
}
