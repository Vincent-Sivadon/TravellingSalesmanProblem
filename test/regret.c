#include "TSP.h"
#include "Utility.h"
#include "Initialization.h"

#include <stdlib.h>
#include <assert.h>

void getRegretTest()
{
    int * adj;
    int N;
    fileInitialization("../edges.txt", &adj, &N);

    Problem * p = newProblem();
    p->adj = adj;
    p->N = N;
    bound(p);

    assert(getRegret(p->adj, N, 2, 1) == 9);
    assert(getRegret(p->adj, N, 4, 3) == 6);
}

void getArcOfMaxRegretTest()
{
    int * adj;
    int N;
    fileInitialization("../edges.txt", &adj, &N);

    Problem * p = newProblem();
    p->adj = adj;
    p->N = N;
    bound(p);
    Arc * arc_of_max_regret = getArcOfMaxRegret(adj, N);

    assert(arc_of_max_regret->i == 2);
    assert(arc_of_max_regret->j == 1);
}

int main(int argc, char const *argv[])
{
    getRegretTest();
    printf("getRegret test passed\n");

    getArcOfMaxRegretTest();
    printf("getArcOfMaxRegret test passed\n");

    return 0;
}
