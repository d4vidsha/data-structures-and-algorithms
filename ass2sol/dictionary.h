#include "record_struct.h"
#include <stdio.h>

#define LOOKUPSTAGE 1
#define PROXIMITYSTAGE 2
#define QTLOOKUP 3
#define QTPRLOOKUP 4

/* Result of a query. */
struct queryResult;

/* Dictionary. */
struct dictionary;

/* Returns an empty dictionary. */
struct dictionary *newDict();

/* Sets the bounds for point region quadtree lookup functions. pointsStart is
    a list of dim long double values correseponding to the start of the 
    Point Region initial rectangle, the lower bounds. pointsEnd is 
    the corresponding list of upper bounds. indices is a list of 
    fieldIndexCount indices pointing to fields in the dictionary. */
void reconfigureSearchBounds(struct dictionary *dict, long double *pointsStart, 
    long double *pointsEnd, unsigned int dim, unsigned int **indices, 
    unsigned int fieldIndexCount);

/* Insert a given record into the dictionary. */
void insertRecord(struct dictionary *dict, struct csvRecord *record);

/* Search for a given key in the dictionary. */
struct queryResult *lookupRecord(struct dictionary *dict, char *query);

/* Search for the closest record in the dictionary to the query string in the given
    field index. Assumes the field selected is double type. */
struct queryResult *searchClosestDouble(struct dictionary *dict, char *query, 
    int fieldIndex);

/* Search for the point which lays in the same point region as the given 
    query. Sorts results by primary key field given by fieldIndex. */
struct queryResult *searchQT(struct dictionary *dict, char *query, 
    int fieldIndex);

/* Return all points which lay in the point region given in the query. 
    Sorts results by primary key field given by fieldIndex. */
struct queryResult *searchPR(struct dictionary *dict, char *query, 
    int fieldIndex);

/* Output the given query result. */
void printQueryResult(struct queryResult *r, FILE *summaryFile, 
    FILE *outputFile, int stage);

/* Free the given query result. */
void freeQueryResult(struct queryResult *r);

/* Free a given dictionary. */
void freeDict(struct dictionary *dict);

