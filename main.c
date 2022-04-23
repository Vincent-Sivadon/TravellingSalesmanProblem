#include "TSP.h"

#include "Utility.h"

int main(int argc, char const *argv[])
{
    int * mat = fileInitialization("edges.txt");
    TSP(mat, 4);
    //displayMatrixTerminal(mat, 4);
    return 0;
}
