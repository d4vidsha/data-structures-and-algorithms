#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "adjmatrix.h"

int **newMatrix(int size){
    int **retMatrix;
    int i, j;
    retMatrix = (int **) malloc(sizeof(int *)*size);
    assert(retMatrix);
    for(i = 0; i < size; i++){
        retMatrix[i] = (int *) malloc(sizeof(int)*size);
        assert(retMatrix[i]);
        for(j = 0; j < size; j++){
            retMatrix[i][j] = NOPATH;
        }
    }
    return retMatrix;
}

void addEdge(int **adjMatrix, int src, int dst, int weight){
    adjMatrix[src][dst] = weight;
}

void freeMatrix(int **matrix, int size){
    if(!matrix){
        return;
    }
    int i;
    for(i = 0; i < size; i++){
        free(matrix[i]);
    }
    free(matrix);
}
