struct digraph;

struct weightedEdge;

#ifndef WEIGHTEDEDGE
#define WEIGHTEDEDGE
/* Return type for edges. 
    Linked list concrete data type. */
struct weightedEdge {
    int destIndex;
    int weight;
    struct weightedEdge *next;
    /* 
        The index of the edge in the graph - set by addEdge in the order edges
        are added. 
    */
    int edgeNumber;
};
#endif

/* Create a new weighted directed graph containing no edges. */
struct digraph *newDigraph();

/* Get the number of nodes in the graph. */
int getNodeCount(struct digraph *graph);

/* Get the number of edges in the graph. */
int getEdgeCount(struct digraph *graph);

/* 
    Add an edge from the source to the destination with the given weight
    to the given graph.
*/
void addEdge(struct digraph *graph, int source, int destination, int weight);

/*
    Gets the edge number for the given source and destination in the given
    graph.
*/
int fetchEdge(struct digraph *graph, int source, int destination);

/*
    The returned list is allocated as a linked list of weighted edges. This should be
    freed by the calling function.
*/
struct weightedEdge *getAdjacent(struct digraph *graph, int sourceIndex);

/*
    Frees all the memory used by a particular graph.
*/
void freeDigraph(struct digraph *graph);
