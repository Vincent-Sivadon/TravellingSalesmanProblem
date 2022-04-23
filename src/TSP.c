/* */

#include "TSP.h"

#include <stdlib.h>
#include "limits.h"

/* Branch and Bound Node */
typedef struct {
    Arc * arcMaxRegret;
    int eval;
} Node;

/* */
int evaluate(int * mat, int N)
{
    // Final evaluation
    int eval = 0;

    // Will store the minimum of each line
    int lignMinimums[N];

    // For all lign i, store the minimum and add it to eval
    for (int i=0 ; i<N ; i++)
    {
        lignMinimums[i] = minLign(mat, N, i);
        eval += lignMinimums[i];
    }
    
    // For all col j, add the min - lignMinimums[j]
    for (int j=0 ; j<N ; j++)
    {
        // Minimum arc value of that col
        int min = INT_MAX;

        // Search for the minimum value of the column
        for (int i=0 ; i<N; i++)
            if (mat[i*N + j] - lignMinimums[i] < min && mat[i*N + j] != -1)
                min = mat[i*N + j] - lignMinimums[i];
        
        eval += min;
    }

    return eval;
}

/* Get regret for the Arc {i,j} */
int arcRegret(int * mat, int N, int i, int j)
{
    int minL = minLign(mat, N, i);
    int minC = minCol(mat, N, j);

    return minL + minC;
}

/* Retrieve the Arc of max regret 
 * in matrix mat of size N */
Arc arcMaxRegret(int * mat, int N)
{
    Arc arcOfMaxRegret;
    int maxRegret = INT_MAX;

    // Regrets computation
    for (int i=0 ; i<N ; i++)
        for (int j=0 ; j<N ; j++)
            if (mat[i*N + j] == 0)
            {
                int regret = arcRegret(mat, N, i, j);

                if (regret > maxRegret)
                {
                    maxRegret = regret;
                    arcOfMaxRegret.i = i;
                    arcOfMaxRegret.j = j;
                    arcOfMaxRegret.regret = regret;
                }
            }

    return arcOfMaxRegret;
}

/* */
Arc * TSP(int * mat, int N)
{
    // Store Current, sub-problem 1 and 2
    Node currNode, sp1, sp2;

    Arc * arcQueueHead = NULL;
    arcQueueHead = (Arc *) malloc(sizeof(Arc));
    arcQueueHead->id = 0;
    currNode.eval = evaluate(mat, N);
    *currNode.arcMaxRegret = arcMaxRegret(mat, N);

    while (arcQueueHead->id < N-1)
    {
        sp2.eval = currNode.eval + currNode.arcMaxRegret->regret;
        sp1.eval = evaluate(mat, N);
        if (sp1.eval <= sp2.eval)
        {
            // Insert arc0 to queue
            currNode.arcMaxRegret->next = arcQueueHead;
            currNode.arcMaxRegret->id = arcQueueHead->id + 1;
            arcQueueHead = currNode.arcMaxRegret;

            // Update next current node
            currNode = sp1;
            reduce(mat, N, currNode.arcMaxRegret);
            *currNode.arcMaxRegret = arcMaxRegret(mat, N);
        }
        else
        {
            currNode = sp2;
            // treat matrix : mask the arc ?
            *currNode.arcMaxRegret = arcMaxRegret(mat, N);
        }
    }

    return arcQueueHead;
}