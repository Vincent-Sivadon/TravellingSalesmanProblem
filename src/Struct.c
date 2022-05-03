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

    return p;
}

int checkInsertion(Arc *queue, Arc * arc)
{
    int start = arc->i;
    while (queue != NULL)
    {

        // If there is a cycle
        if (queue->j == start) return 0;

        // If we don't have continuity anymore, we passed the test
        if (queue->next != NULL && queue->j != queue->next->i)
            return 1;
        queue = queue->next;

    }

    return 1;
}

void insertArc(Arc ** queue, Arc * arc)
{
    // Previous head with on arc late
    Arc * current = *queue;

    while (current->next != NULL)
    {
        if ( arc->j == current->next->i)
        {
            // vérifier si c'est une pièce manquante du puzzle
            // (il existe 2 noeud tel que arc->i == node1->j et arc->j = node2->i)
            Arc * nested_current = *queue;
            while (nested_current->next != NULL)
            {
                if (arc->i == nested_current->next->j)
                {
                    // Insert after nested_current->next
                    if (!checkInsertion(nested_current->next, arc)) return;
                    arc->next = nested_current->next->next;
                    nested_current->next->next = arc;
        
                    Arc * new = newArc(current->next->i, current->next->j);
                    insertArc(queue,new);
                    return;
                }
                nested_current = nested_current->next;
            }
            // Insert after current
            if (!checkInsertion(current, arc)) return;
            arc->next = current->next;
            current->next = arc;
            return;
        }
        else if (arc->i == current->next->j)
        {
            // Insert after current->next
            if (!checkInsertion(current->next, arc)) return;
            arc->next = current->next->next;
            current->next->next = arc;
            return;
        }
        current = current->next;
    }

    // If we made it here, insert at the beginning
    if (current->next == NULL) {
        if (!checkInsertion(*queue, arc)) return;
        arc->next = *queue;
        *queue = arc;
    }
}