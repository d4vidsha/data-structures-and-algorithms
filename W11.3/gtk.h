/* These are helpers for the graphics library, gtk. */
struct gtkContext;

/* Call to start GTK. */
void setupGTK(int *argc, char ***argv, char *title);

/* Call to set GTK graph. */
void setupGTKgraph(int nodeCount, int edgeCount, int *sources, int *destinations, 
    int *weights, char **vertexLabels);

/* Call to set dijkstra interface functions. */
void setupGTKdijkstra(void *digraph, 
    void *(*dijkstra)(void *graph, int source), 
    void (*constructPath)(void *res, void *graph, int *path, 
        int destination), 
    void (*freeDijkstraRes)(void *res));

/* Call to set up dijkstra online functions. */
void setupGTKDijkstraOnline(void *digraph, 
    void *(*dijkstra)(void *graph, int source),
    void *(*dijkstraUpdate)(void *graph, void *oldRes, int edgeSource, 
        int edgeDestination, int edgeWeight),
    void (*constructPath)(void *res, void *graph, int *path, 
        int destination), 
    void (*freeDijkstraRes)(void *res),
    void (*addEdge)(void *graph, int source, int destination, int weight),
    int nodeCount, 
    int edgeCount, 
    int *sources, 
    int *destinations, 
    int *weights, 
    char **vertexLabels);

/* Begin interactive GTK portion. */
void runGTKInteraction();

/* Free GTK allocations. */
void freeGTK();

/* Call to set Floyd-Warshall interface functions. */
void setupGTKFW(int **graph, 
    void (*fw)(int **adjMatrix, int ***pathMatrix, int size), 
    void (*constructPathFW)(int **adjMatrix, int **pathMatrix, int *path, int source, 
    int destination, int size), 
    void (*printPath)(int **pathMatrix, int src, int dest));

