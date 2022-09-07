/* =============================================================================
   Project: Assignment 2 (altered from Assignment 1)
   search.h :
            = all related to searching
============================================================================= */
#ifndef _SEARCH_H_
#define _SEARCH_H_

/* #includes ================================================================ */
#include "data.h"
#include "linkedlist.h"
#include "quadtree.h"
#include "print.h"

/* function prototypes ====================================================== */
list_t *find_addresses(char *address, list_t *list);
list_t *linearsearch(double value, list_t *list);
array_t *binarysearch(double val, array_t *A);
dpll_t *search_quadtree(qtnode_t *root, point2D_t *p);
dpll_t *range_search_quadtree(qtnode_t *root, rectangle2D_t *range);
void _range_search_quadtree(dpll_t *res, qtnode_t *root, rectangle2D_t *range);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */