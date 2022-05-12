# Travelling Salesman Problem
Solver for the TSP (Travelling Salesman Problem) using max-regrets branch and bound method.  
We consider valued directed complete graphs.
# Features
Basic usage (detailed below) :  
```
$ make
$ ./TSP graph.txt
0 3 2 1 4 0
```
# Usage
A call to the solver will be :
```
Arc * queue = TSP("graph.txt");
```
And to print the result :
```
printNodeQueue(queue);
```
That will ouput something like :  `0 3 2 4 1 0`, which means the best found path is to go from 0 to 3 to 2...  
The text input, in the exemple "mat.txt", should represent an adjacency matrix like :
```
x 3 4 2 7
3 x 4 6 3
4 4 x 5 8
2 6 5 x 6
7 3 8 6 x
```
where x will in the program be changed in -1 and represent ignored values.  
There's already in the repository few files to test the program on.  
Files that starts with `city` were taken on the website : https://people.sc.fsu.edu/~jburkardt/datasets/tsp/tsp.html.  
The file `graph.txt` is an exemple from the article : https://hal.archives-ouvertes.fr/hal-00152332/document.

# Build
At the top level of the repository, `make` will build a library `libTSP.so` in the lib sub-directory, and a few object files in the src sub-directory. All those build files can be cleaned with the command `make clean`.  
The file at the top level of the repository `TSP.c` creates a binary `TSP` that when called with a adjacency matrix file, will compute and print the result of the TSP solver.