/* =============================================================================
   Project: Assignment 1
   quicksort.h :
            = all related to quicksort
============================================================================= */
#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

/* #includes ================================================================ */
#include "data.h"
#include "linkedlist.h"

/* function prototypes ====================================================== */
void quicksort(list_t *list, int col);
node_t *partition(node_t *low, node_t *high, int col);
void swap(node_t *n1, node_t *n2);
node_t *get_prev_node(node_t *start, node_t *node);
double cmp_column(int col, footpath_segment_t *n, footpath_segment_t *m);
double cmp_grade1in(double n, double m);
int cmp_address(char *n, char *m);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */