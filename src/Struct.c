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

    // Define values
    p->sub1 = NULL;
    p->sub2 = NULL;

    return p;
}