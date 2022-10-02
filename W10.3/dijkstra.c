#include "digraph.h"
#include "dijkstra.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pqueue.h"

struct dijkstraRes *dijkstra(struct digraph *graph, int source){
    int i;
    
    struct dijkstraRes *res = (struct dijkstraRes *) 
        malloc(sizeof(struct dijkstraRes));
    assert(res);
    res->sourceNode = source;

    res->shortestPaths = NULL;
    res->prev = NULL;

    int nodeCount = getNodeCount(graph);
    
    /* FILL IN HERE */
    /* 
        Note: You have been provided with:
         - a priority queue (pq.h)
         - a function to get the neighbours of a given node (getAdjacent)
    */
    /* Initialise shortestPaths and prev. */
        
    /* Initialise a seen array */
    
    /* Run Dijkstra's Algorithm. */
    struct pq *p = newPQ();
    struct weightedEdge *adjacent;
    struct weightedEdge *last;
    /* Set the shortest distance to the source node to 0 */
    (res->shortestPaths)[source] = 0;
    /* Set the previous node on the shortest path to the 
    source node as the source node itself */
    (res->prev)[source] = source;
    /* Add the source vertex to the priority queue with
    priority 0 */
    enqueue(p, (void *) (size_t) source, 0);
    /* The current vertex we're working with */
    int current;
    
    while(! empty(p)){
        current = (int) (size_t) deletemin(p);
        /* Priority queue doesn't have update cost
        function, so we use a "seen" array to avoid 
        redundant work */
        if((seen)[current]){
            continue;
        } else {
            (seen)[current] = 1;
        }
        /* FILL IN - loop through adjacent vertices */
    }
    
    freePQ(p);
    return res;
}

/*
    Construct the path to the requested destination using an existing dijkstraRes.
    res is the dijkstraRes structure you built.
    graph is the digraph the dijkstraRes was built on.
    path is an array the same size as the number of edges in the graph, initialised
        to all 0s. After running constructPath, all edges used in the path should 
        have a 1 in that position.
    destination is the destination which the path should be constructed to.
*/
void constructPath(struct dijkstraRes *res, struct digraph *graph, int *path, 
    int destination){
    /* FILL IN HERE */
    /* NOTE: This is a hard-coded example which adds 1 -> 2 -> 3 in the 
        example graph. */
    if(!res || ! res->prev){
        path[0] = 1;
        path[3] = 1;
    }
    if(res->prev[destination] == NOPATH){
        /* No path. */
        return;
    }
    int current = destination;
    int source = res->sourceNode;
    
    while(current != source){
        path[fetchEdge(graph, res->prev[current], current)] = 1;
        current = res->prev[current];
    }
}

void printDijkstra(struct dijkstraRes *res, struct digraph *g){
    int i;
    printf("Shortest paths from %d\n", res->sourceNode);
    for(i = 0; i < getNodeCount(g); i++){
        if ((res->shortestPaths[i]) == NOPATH){
            printf("to %d: NO PATH;\n", i);
        } else {
            printf("to %d: %d;\n", i, res->shortestPaths[i]);
        }
    }
}

void freeDijkstraRes(struct dijkstraRes *res){
    if(! res){
        return;
    }
    if(res->shortestPaths){
        free(res->shortestPaths);
    }
    free(res);
}
