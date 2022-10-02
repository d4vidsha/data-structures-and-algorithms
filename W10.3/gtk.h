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

/* Begin interactive GTK portion. */
void runGTKInteraction();

/* Free GTK allocations. */
void freeGTK();
