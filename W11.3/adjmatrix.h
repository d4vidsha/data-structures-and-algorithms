#include <limits.h>
#define NOPATH INT_MAX/2
/* Allocates space for a size * size array
    and sets all values to the NOPATH value. */
int **newMatrix(int size);

/* Adds an edge between one given index and another. */
void addEdge(int **adjMatrix, int src, int dst, int weight);

/* Frees a matrix allocated with the newMatrix function. */
void freeMatrix(int **matrix, int size);
