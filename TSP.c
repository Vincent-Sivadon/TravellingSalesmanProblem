#include "TSP.h"

#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage : %s [filename]\n", argv[0]);
        return 1;
    }

    Arc * queue = TSP(argv[1]);
    printNodeQueue(queue);

    return 0;
}
