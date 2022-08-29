/* =============================================================================
   Project: Assignment 2 (imported from Assignment 1)
   search.h :
            = all related to searching
============================================================================= */
#ifndef _SEARCH_H_
#define _SEARCH_H_

/* #includes ================================================================ */
#include "data.h"
#include "linkedlist.h"

/* function prototypes ====================================================== */
list_t *find_addresses(char *address, list_t *list);
list_t *linearsearch(double value, list_t *list);
array_t *binarysearch(double val, array_t *A);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */