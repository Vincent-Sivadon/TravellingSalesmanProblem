#include "TSP.h"

#include <stdlib.h>

int main(int argc, char const *argv[])
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



    TSP(p);

    return 0;
}
