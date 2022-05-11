#include "Regret.h"

#include <limits.h>

/* Given (k,l) representing an arc of adj, returns it's regret */
int getRegret(int * adj, int N, int k, int l)
{
    int minLign = INT_MAX;
    int minCol  = INT_MAX;
    
    // Run through the column
    for (int i=0 ; i<N ; i++)
        if (i!= k && adj[i*N + l] != -1 && adj[i*N + l] < minCol)
            minCol = adj[i*N + l];
    
    // Run through all the ligns
    for (int j=0 ; j<N ; j++)
        if (j!= l && adj[k*N + j] != -1 && adj[k*N + j] < minLign)
            minLign = adj[k*N + j];

    // Means ligns and cols surrounding it have only -1
    // So it's the only arc that can be picked
    if (minLign == INT_MAX) return 0;


    return minCol + minLign;
}

/* Returns the arc of max regret given a graph of size N represented by adj */
Arc * getArcOfMaxRegret(Problem * p)
{
    // Init
    Arc * arc_of_max_regret = newArc(-1, -1);

    int max_regret = -1;

    int count = 0;
    for (int i=0 ; i<p->N ; i++)
        for (int j=0 ; j<p->N ; j++)
            if (p->adj[i*p->N + j] == 0)
            {
                count++;
                int regret = getRegret(p->adj, p->N, i, j);
                if (regret > max_regret) 
                {
                    arc_of_max_regret->i = i;
                    arc_of_max_regret->j = j;
                    max_regret = regret;
                }
            }

    // If this arc implies a cycle
    // Out this arc in adj and pick a new one
    if (!checkCycles(p->queue, arc_of_max_regret->i, arc_of_max_regret->j))
    {
        p->adj[arc_of_max_regret->i*p->N + arc_of_max_regret->j] = -1;
        arc_of_max_regret = getArcOfMaxRegret(p);
    }
    

    return arc_of_max_regret;
}

/* When there's only 2 arcs left
 * we must adapt the procedure a bit
 * mainly we can't bound sub1 or we'll
 * loose the last regret information */
void addLastArcs(Problem * p)
{
    //
    int N = p->N;
    int regret = 0;

    Arc * arc = getArcOfMaxRegret(p);
    maskLignCol(p->adj, p->N, arc->i, arc->j);
    addToQueue(&p->queue, arc->i, arc->j);
    regret += getRegret(p->adj, p->N, arc->i, arc->j);
    
    // Search for the last arc in adj
    // (getArcOfMaxRegret won't' work here)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (p->adj[i*N+ j] != -1)
            {
                arc->i = i;
                arc->j = j;
                regret += p->adj[i*N+j];
            }    
    addToQueue(&p->queue, arc->i, arc->j);

    p->bound += regret;
}