#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "digraph.h"

struct digraph{
    int highIndex;
    struct weightedEdge **adjacencyList;
    int allocated;
    int used;
    int edgeCount;
};

struct digraph *newDigraph(){
    struct digraph *retDigraph = (struct digraph *) malloc(sizeof(struct digraph));
    assert(retDigraph);
    
    /* Don't initialise until we have at least one edge so we don't go over-allocate. */
    retDigraph->adjacencyList = NULL;
    retDigraph->allocated = 0;
    retDigraph->used = 0;
    /* Used for edge metadata. */
    retDigraph->edgeCount = 0;
    retDigraph->highIndex = 0;
    
    return retDigraph;
}

int getNodeCount(struct digraph *graph){
    if(! graph){
        return 0;
    } else {
        return graph->used;
    }
}

/* Get the number of edges in the graph. */
int getEdgeCount(struct digraph *graph){
    if(! graph){
        return 0;
    } else {
        return graph->edgeCount;
    }
}

void addEdge(struct digraph *graph, int source, int destination, int weight){
    int initialSize;
    int i;
    struct weightedEdge *newEdge;
    if(source < 0 || destination < 0){
        fprintf(stderr, "Node indices must be >= 0\n");
        exit(EXIT_FAILURE);
    }
    if(! graph->allocated){
        /* Allocate sufficient space for indices. */
        if(source > destination){
            initialSize = source + 1;
        } else {
            initialSize = destination + 1;
        }
        graph->adjacencyList = (struct weightedEdge **) 
            malloc(sizeof(struct weightedEdge *)*initialSize);
        assert(graph->adjacencyList);
        graph->allocated = initialSize;
        /* Initialise edge list. */
        for(i = 0; i < initialSize; i++){
            (graph->adjacencyList)[i] = NULL;
        }
        /* Initialise low and high indices. */
        if(source > graph->highIndex){
            graph->highIndex = source;
        }
        if (destination > graph->highIndex){
            graph->highIndex = destination;
        }
        graph->used = graph->highIndex + 1;
    } else {
        /* Ensure we have space for the new edge */
        if(graph->highIndex < source || graph->highIndex < destination){
            if(source > destination){
                graph->highIndex = source;
            } else {
                graph->highIndex = destination;
            }
            if(graph->highIndex >= graph->allocated){
                graph->adjacencyList = (struct weightedEdge **) 
                    realloc(graph->adjacencyList, 
                    sizeof(struct weightedEdge *)*graph->allocated * 2);
                assert(graph->adjacencyList);

                for(i = graph->allocated; i < (graph->allocated * 2); i++){
                    (graph->adjacencyList)[i] = NULL;
                }

                graph->allocated = graph->allocated * 2;
                graph->used = graph->highIndex + 1;
            }
        }
        if(graph->highIndex >= graph->used){
            graph->used = graph->highIndex + 1;
        }
    }
    
    /* Add the edge to the relevant place [prepend the list]. */
    newEdge = (struct weightedEdge *) malloc(sizeof(struct weightedEdge));
    assert(newEdge);
    newEdge->destIndex = destination;
    newEdge->weight = weight;
    newEdge->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = newEdge;
    /* Set metadata. */
    newEdge->edgeNumber = graph->edgeCount;
    graph->edgeCount = graph->edgeCount + 1;
}

struct weightedEdge *getAdjacent(struct digraph *graph, int sourceIndex){
    struct weightedEdge *current = NULL;
    struct weightedEdge *returnList = NULL;
    struct weightedEdge *currentGraph = NULL;
    
    currentGraph = graph->adjacencyList[sourceIndex];
    if(currentGraph){
        while(currentGraph){
            /* Move current to its next value. */
            if(! current){
                returnList = (struct weightedEdge *) malloc(sizeof(struct weightedEdge));
                assert(returnList);
                current = returnList;
            } else {
                current->next = (struct weightedEdge *) malloc(sizeof(struct weightedEdge));
                assert(current->next);
                current = current->next;
            }
            /* Append value. */
            current->next = NULL;
            current->weight = currentGraph->weight;
            current->destIndex = currentGraph->destIndex;
            currentGraph = currentGraph->next;
        }
        return returnList;
    } else {
        /* No edges for source index. */
        return NULL;
    }
}

int fetchEdge(struct digraph *graph, int source, int destination){
    struct weightedEdge *current = (graph->adjacencyList)[source];
    while(current){
        if(current->destIndex == destination){
            return current->edgeNumber;
        }
        current = current->next;
    }
    return 0;
}

void freeDigraph(struct digraph *graph){
    int i;
    struct weightedEdge *current;
    struct weightedEdge *next;
    if(!graph){
        return;
    }
    for(i = 0; i < graph->allocated; i++){
        if(graph->adjacencyList[i]){
            current = graph->adjacencyList[i];
            graph->adjacencyList[i] = NULL;
            while(current){
                next = current->next;
                free(current);
                current = next;
            }
        }
    }
    if(graph->allocated > 0){
        free(graph->adjacencyList);
    }
    free(graph);
}