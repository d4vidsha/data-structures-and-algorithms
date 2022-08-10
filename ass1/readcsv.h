/* =============================================================================
   Project: dict1
   readcsv.h :
            = related all to reading from input
============================================================================= */

#ifndef _READCSV_H_
#define _READCSV_H_
#include "readin.h"
#include "data.h"
#include "linkedlist.h"

/* #defines ================================================================= */
#define COMMA ','
#define DOUBLEQUOTE '"'
#define NULLBYTE '\0'
#define TRUE 1
#define FALSE 0

/* #includes ================================================================ */

/* typedefs ================================================================= */

/* function prototypes ====================================================== */
int is_in_cell_length(int curr, int max);
void get_str(FILE *f, char *string);
int get_int(FILE *f);
double get_double(FILE *f);


#endif

/* =============================================================================
   Written by David Sha.
============================================================================= */
