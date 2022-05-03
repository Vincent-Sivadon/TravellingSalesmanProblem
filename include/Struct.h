#pragma once

/* Represent an arc between two nodes i and j in a graph
 * Points towards next so we can build chained arc lists */
struct Arc {
    int i,j;            // the 2 nodes this arc connects
    struct Arc * next;  // the next arc in queue
}; typedef struct Arc Arc;

/* Create new arc */
Arc * newArc(int i, int j);

/* Add an Arc to a queue of arcs */
void addToQueue(Arc ** queue, int i, int j);


/* ============================================================================= */


/* Represent a given problem */
struct Problem {
    int * adj;              // Adjacency Matrix
    int N;                  // Square root of the 1D size of adj (max node index)

    Arc * queue;            // Queue of selected arcs
    Arc arc_of_max_regret;  // Arc that has the highest regret
    int bound;              // Evaluation of this problem

    struct Problem * sub1;  // Pointer to a first subproblem
    struct Problem * sub2;  // Pointer to a second subproblem

}; typedef struct Problem Problem;


/* Create new problem */
Problem * newProblem();