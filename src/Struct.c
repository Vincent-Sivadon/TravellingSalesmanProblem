/* Travelling Salesman Data Structures */

#include "Struct.h"

#include <stdlib.h>

/* Create new arc */
Arc * newArc(int i, int j)
{
    // Allocate memory
    Arc * arc = (Arc *) malloc(sizeof(Arc));

    // Define values
    arc->i = i;
    arc->j = j;
    arc->next = NULL;

    return arc;
}

/* Check if the insertion of the Arc (i,j) in queue will imply a cycle 
 * Returns 0 if it does, 1 if not */
int checkCycles(Arc *queue, int i, int j)
{
    Arc * curr = queue;
    while (curr != NULL)
    {
        if (curr->i == j)
        {
            j = curr->j;
            if (j==i) return 0;
            curr = queue;
        } else {
            curr = curr->next;
        }
    }

    return 1;
}

/* Add an Arc to a queue of arcs */
void addToQueue(Arc ** queue, int i, int j)
{
    // Create new Arc
    Arc * new_arc = newArc(i,j);

    // Make so it points towards the queue
    new_arc->next = *queue;

    // We have constructed newArc->queue0->queue1...
    *queue = new_arc;
}

/* Create new problem */
Problem * newProblem()
{
    // Allocate memory
    Problem * p = (Problem *) malloc(sizeof(Problem));

    return p;
}


void freeQueue(Arc *queue)
{
    while (queue != NULL)
    {
        Arc * tmp = queue;
        queue = queue->next;
        free(tmp);
    }
}

void freeProblem(Problem *p)
{
    freeQueue(p->queue);
    free(p->adj);
    free(p);
}