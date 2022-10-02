#include <stdio.h>
#include <stdlib.h>
#include "digraph.h"
#include "dijkstra.h"
#include "gtk.h"
#define EDGES 6
#define NODES 6

int main(int argc, char **argv){
    struct digraph *graph = NULL;
    #ifndef USE_GUI
    struct dijkstraRes *res = NULL;
    #endif
    int src[EDGES];
    int dest[EDGES];
    int weight[EDGES];
    #ifdef USE_GUI
    char labels[NODES][2];
    char *vertexLabels[NODES];
    #endif
    int i = 0;
    src[i] = 1; dest[i] = 2; weight[i] = 200; i++;
    src[i] = 1; dest[i] = 3; weight[i] = 100; i++;
    src[i] = 1; dest[i] = 4; weight[i] = 500; i++;
    src[i] = 2; dest[i] = 3; weight[i] = 150; i++;
    src[i] = 2; dest[i] = 4; weight[i] = 300; i++;
    src[i] = 4; dest[i] = 5; weight[i] = 100;
    #ifdef USE_GUI
    for(i = 0; i < NODES; i++){
        labels[i][0] = 'A' + i;
        labels[i][1] = '\0';
        vertexLabels[i] = &(labels[i][0]);
    }
    #endif
    
    graph = newDigraph();
    
    for(i = 0; i < EDGES; i++){
        addEdge(graph, src[i], dest[i], weight[i]);
    }

    /* Set up GTK if we have the GUI on. */
    #ifdef USE_GUI
    setupGTK(&argc, &argv, "Dijkstra's Algorithm");
    setupGTKgraph(getNodeCount(graph), getEdgeCount(graph), src, dest, weight, vertexLabels);
    /* 
        To silence the errors and tell GCC we know what we're doing by stripping
        the types, we typecast these function pointers to their (void *) versions.
    */
    setupGTKdijkstra(graph, 
        (void * (*)(void *, int)) &dijkstra, 
        (void (*)(void *, void *, int *, int)) &constructPath, 
        (void (*)(void *)) &freeDijkstraRes);

    runGTKInteraction();
    freeGTK();
    #else
    for(i = 0; i < getNodeCount(graph); i++){
        printf("Running Dijkstra's Algorithm on graph, starting from %d\n", i);
        res = dijkstra(graph, i);
        printf("Results:\n");
        printDijkstra(res, graph);
        freeDijkstraRes(res);
    }
    #endif

    freeDigraph(graph);
    
    return 0;
}