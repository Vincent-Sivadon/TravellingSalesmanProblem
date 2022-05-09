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
    // Conditions for a cycle
    int has_already_entered_i = 0;
    int has_already_exit_j    = 0;

    // Run through all arcs in queue
    while (queue != NULL)
    {
        if (queue->i == j)
            has_already_exit_j = 1;
        if (queue->j == i)
            has_already_entered_i = 1;

        queue = queue->next;
    }

    if (has_already_entered_i && has_already_exit_j)
        return 0;
    return 1;
}

/* Add an Arc to a queue of arcs */
int addToQueue(Arc ** queue, int i, int j)
{
    // Check if inserting this arc will cause a cycle
    if (!checkCycles(*queue, i, j))
        return 0;

    // Create new Arc
    Arc * new_arc = newArc(i,j);

    // Make so it points towards the queue
    new_arc->next = *queue;

    // We have constructed newArc->queue0->queue1...
    *queue = new_arc;

    // Means we could indeed insert the arc
    return 1;
}

/* Create new problem */
Problem * newProblem()
{
    // Allocate memory
    Problem * p = (Problem *) malloc(sizeof(Problem));

    return p;
}
