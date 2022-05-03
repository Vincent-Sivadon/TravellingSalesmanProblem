#include "Initialization.h"
#include "Utility.h"
#include "TSP.h"

#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int * adj;
    int N;
    fileInitialization("edges.txt", &adj, &N);

    //TSP(adj, N);
    //displayMatrixTerminal(adj, N);


    return 0;
}
