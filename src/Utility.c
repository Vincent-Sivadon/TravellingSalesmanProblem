#include "Utility.h"

/* Print Matrix mat of order N in terminal*/
void printMatrix(int *mat, int N)
{
    printf("-----------------------\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i * N + j]);
        printf("\n");
    }
    fflush(stdout);
}

/* Print all the arc of queue in terminal */
void printArcQueue(Arc * queue)
{
    printf("-----------------------\n");
    while (queue != NULL)
    {
        printf("%d - %d\n", queue->i, queue->j);
        queue = queue->next;
    }
    fflush(stdout);
}

/* Print the node visited in order in terminal */
void printNodeQueue(Arc * queue)
{    
    int i = 0;
    int loop_count = 0;
    Arc * current = queue;
    while (loop_count < 2)
    {
        printf("%d ", i);

        if (i==0)
            loop_count++;

        current = queue;
        int t=-1;
        while (current != NULL)
        {
            if (current->i == i)
            {
                i = current->j;
                t = 0;
                break;
            }
            current = current->next;
        }
        if (t == -1)
            loop_count++;

    }

    printf("\n");
    fflush(stdout);
}

/* Return a copy of queue */
Arc * copyQueue(Arc * queue)
{
    Arc *queue_copy = newArc(-1,-1);

    while (queue != NULL)
    {
        if (queue->i != -1)
            addToQueue(&queue_copy, queue->i, queue->j);
        queue = queue->next;
    }
    
    return queue_copy;
}

/* Change all the element of lign l and col c to -1 */
void maskLignCol(int * adj, int N, int l, int c)
{
    for (int i=0 ; i<N ; i++)
        adj[i*N + c] = -1;
    for (int j=0 ; j<N ; j++)
        adj[l*N + j] = -1;
}