#include "Initialization.h"
#include "Utility.h"
#include "TSP.h"
#include "Struct.h"

#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int * adj;
    int N;
    fileInitialization("edges.txt", &adj, &N);

    Problem * p = newProblem();
    p->adj = adj;
    p->N = N;
    p->queue = newArc(-1,-1);
    p->queue_size = 0;
    bound(p);

    //TSP(p);

    Arc * queue = newArc(1,2);
    Arc * new = newArc(0,1);
    Arc * new2 = newArc(2, 0);
    insertArc(&queue, new);
    insertArc(&queue, new2);
    displayArcQueue(queue);

    return 0;
}
