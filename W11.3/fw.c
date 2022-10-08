#include "fw.h"
#include "adjmatrix.h"
#include <stdlib.h>
#include <stdio.h>

void fw(int **adjMatrix, int ***pathMatrix, int size){
    /* FILL IN */
}

void printPath(int **pathMatrix, int src, int dest){
    /* FILL IN */
    printf("(Not yet handled)");
}

/*
    Construct the path to the requested destination using an existing pathMatrix.
    adjMatrix is the shortest path matrix constructed by 
    pathMatrix is the pathMatrix structure you built.
    graph is the digraph the pathMatrix was built on.
    path is an array of size size*size as the number of edges in the graph, 
        initialised to all 0s. After running constructPath, all edges used 
        in the path should have a 1 in that position.
    source is the source the path should begin from.
    destination is the destination which the path should be constructed to.
*/
void constructPathFW(int **adjMatrix, int **pathMatrix, int *path, int source, 
    int destination, int size){
    /* NOTE: This is a hard-coded example which adds 1 -> 2 -> 3 in the 
        example graph. */
    if(! pathMatrix){
        path[1 * size + 2] = 1;
        path[2 * size + 3] = 1;
        return;
    }
    if(adjMatrix[source][destination] == NOPATH || 
        pathMatrix[source][destination] == NOPATH){
        /* No path. */
        return;
    }
    int current = source;
    
    while(current != destination && pathMatrix[current][destination] != NOPATH){
        path[current * size + pathMatrix[current][destination]] = 1;
        current = pathMatrix[current][destination];
    }
}

void freePathMatrix(int **pathMatrix, int size){
    int i;
    if(pathMatrix){
        for(i = 0; i < size; i++){
            if(pathMatrix[i]){
                free(pathMatrix[i]);
            }
        }
        free(pathMatrix);
    }
}
