#include "dictionary_struct.h"

#define SUPPORTED_DIMENSIONS 2
/* Directions for step summarisation during search. */
#define DIR_SE 0
#define DIR_NE 1
#define DIR_NW 2
#define DIR_SW 3

struct quadTree;

/* Create a new quadTree with the given bounds. */
struct quadTree *newQuadTree(long double *pointsStart, 
    long double *pointsEnd, unsigned int dim);

/* Insert the given point into the given quadTree. Returns
    1 if the insertion was successful and 0 otherwise. */
int insertQuadTree(struct quadTree *qt, double *point, 
    struct dictionaryNode *data);

/* Search for the point region containing the given point and
    return the associated dictionaryNodes. Stores all directions searched
    to find the point region. */
void searchPoint(struct quadTree *qt, double *point, int *stepCount, 
    int **steps, struct dictionaryNode ***results, int *resultCount);

/* Search for all points in regions overlapping the given rectangle defined
    by the pointStart and pointEnd values. */
void searchRegion(struct quadTree *qt, long double *pointStart, 
    long double *pointEnd, int *stepCount, int **steps, 
    struct dictionaryNode ***results, int *resultCount);

/* Free the given quadTree, data inserted is not freed. */
void freeQuadTree(struct quadTree *qt);
