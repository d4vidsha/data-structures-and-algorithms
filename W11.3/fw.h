/* Finds shortest paths between all nodes and all other nodes.
    Allocates space for path matrix and stores this in the space pointed
    to by pathMatrix. 
    size is the dimension of the matrix. */
void fw(int **adjMatrix, int ***pathMatrix, int size);

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
    int destination, int size);

/* Prints the path from the source node given to the destination node
    given using the given path matrix. The path printed is new line 
    terminated. */
void printPath(int **pathMatrix, int src, int dest);

/* Frees a path matrix and all the values within it. */
void freePathMatrix(int **pathMatrix, int size);
