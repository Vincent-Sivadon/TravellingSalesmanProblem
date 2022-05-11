#include "TSP.h"

#include <stdlib.h>

int main(int argc, char const *argv[])
{
    Arc * queue = TSP("../edges.txt");
    printNodeQueue(queue);

    return 0;
}
