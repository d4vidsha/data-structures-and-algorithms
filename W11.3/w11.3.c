#include <stdio.h>
#include <stdlib.h>
#include "fw.h"
#include "adjmatrix.h"
#include "gtk.h"
#define SIZE 10
#define NUMEDGES 12

int main(int argc, char **argv){
    int **graph = newMatrix(SIZE);
    int **pathMatrix = NULL;
    int i;

    int src[NUMEDGES];
    int dest[NUMEDGES];
    int weight[NUMEDGES];

    #ifdef USE_GUI
    char labels[SIZE][2];
    char *vertexLabels[SIZE];
    #endif

    i = 0;
    src[i] = 0; dest[i] = 4; weight[i] = 2; i++;
    src[i] = 1; dest[i] = 2; weight[i] = 2; i++;
    src[i] = 1; dest[i] = 3; weight[i] = 5; i++;
    src[i] = 1; dest[i] = 4; weight[i] = 10; i++;
    src[i] = 2; dest[i] = 3; weight[i] = 2; i++;
    src[i] = 3; dest[i] = 4; weight[i] = 2; i++;
    src[i] = 3; dest[i] = 5; weight[i] = 6; i++;
    src[i] = 4; dest[i] = 5; weight[i] = 2; i++;
    src[i] = 6; dest[i] = 7; weight[i] = 5; i++;
    src[i] = 6; dest[i] = 8; weight[i] = 9; i++;
    src[i] = 7; dest[i] = 8; weight[i] = 6; i++;
    src[i] = 8; dest[i] = 9; weight[i] = 3; i++;

    #ifdef USE_GUI
    for(i = 0; i < SIZE; i++){
        labels[i][0] = 'A' + i;
        labels[i][1] = '\0';
        vertexLabels[i] = &(labels[i][0]);
    }
    #endif
    
    for(i = 0; i < NUMEDGES; i++){
        addEdge(graph, src[i], dest[i], weight[i]);
    }

    /* Set up GTK if we have the GUI on. */
    #ifdef USE_GUI
    setupGTK(&argc, &argv, "Floyd-Warshall Algorithm");
    setupGTKgraph(SIZE, NUMEDGES, src, dest, weight, vertexLabels);
    /* Set up functions used. */
    setupGTKFW(graph, 
        &fw, 
        &constructPathFW, 
        &printPath);

    runGTKInteraction();
    freeGTK();
    #else
    int j;
    printf("Running Floyd-Warshall's Algorithm on graph\n");
    fw(graph, &pathMatrix, SIZE);
    printf("Shortest path distances:\n");
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            if(graph[i][j] == NOPATH){
                printf(" ∞ ");
            } else {
                printf("%2d ",graph[i][j]);
            }
        }
        printf("\n");
    }
    printf("Paths:\n");
    for(i = 0; i < SIZE; i++){
        printf("Shortest path from %d:\n",i);
        for(j = 0; j < SIZE; j++){
            printf("to %d: ",j);
            printPath(pathMatrix, i, j);
            printf("\n");
        }
    }
    #endif

    freeMatrix(graph, SIZE);
    freePathMatrix(pathMatrix, SIZE);
    
    return 0;
}
