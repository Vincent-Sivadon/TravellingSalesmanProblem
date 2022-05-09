#include "TSP.h"

#include <stdlib.h>
#include <assert.h>

void queueTest()
{
    Arc *queue = newArc(-1, -1);
    addToQueue(&queue, 0, 1);
    addToQueue(&queue, 1, 2);
    addToQueue(&queue, 2, 0);

    // Check that Arc (2,0) hasn't been inserted 
    while (queue != NULL)
    {
        assert(queue->i != 2 && queue->j != 0);
        queue = queue->next;
    }
}

int main(int argc, char const *argv[])
{
    queueTest();

    return 0;
}
