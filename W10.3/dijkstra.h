#include "digraph.h"
#include <limits.h>

#define NOPATH INT_MAX

struct dijkstraRes {
    /* The node that all paths originate from, index is into
        indices list. */
    int sourceNode;
    /* The shortest paths from the source node to
        the destination.  */
    int *shortestPaths;
    /* Previous node in shortest path. */
    int *prev;
};

/* Finds the shortest paths from the given source node to all
    other nodes in the graph (which have at least one edge in either
    direction) and returns a structure of these nodes. 
    Assumes that the given source node is actually in the graph. */
struct dijkstraRes *dijkstra(struct digraph *graph, int source);

/* 
    Prints all the shortest paths.
*/
void printDijkstra(struct dijkstraRes *res, struct digraph *g);

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
    int destination);

/*
    Frees a dijkstraRes struct and all the memory it
    is responsible for. (In the provided code, this is 
    assumed to be: .shortestPaths and .indices, as well
    as the struct sent).
*/
void freeDijkstraRes(struct dijkstraRes *res);