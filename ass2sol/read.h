#include "record_struct.h"
#include <stdio.h>

/* Returns a list of CSV records. */
struct csvRecord **readCSV(FILE *csvFile, int *n);

/* Read a line of input from the given file. */
char *getQuery(FILE *f);

/* Free a set of records. */
void freeCSV(struct csvRecord **dataset, int n);

