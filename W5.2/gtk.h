/* These are helpers for the graphics library, gtk. */
struct gtkContext;

/* Call to start GTK. */
void setupGTK(int *argc, char ***argv, char *title);

/* Call to set GTK graph. */
void setupGTKgraph(int nodeCount, int edgeCount, int *sources, int *destinations, 
    int *data);

/* Call to set tree interface functions. */
void setupGTKtree(void *tree, 
    void *(*dijkstra)(void *graph, int source), 
    void (*constructPath)(void *res, void *graph, int *path, 
        int destination), 
    void (*freeDijkstraRes)(void *res));

/* Call to set function to call. actionContext pointer is given to function */
void setupGTKAction(void (*doAction)(void *, double, double), void *actionContext);

/* Begin interactive GTK portion. */
void runGTKInteraction();

/* Free GTK allocations. */
void freeGTK();

