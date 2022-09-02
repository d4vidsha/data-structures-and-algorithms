/* =============================================================================
   Project: Assignment 2
   print.h :
            = all related to printing structures
============================================================================= */
#ifndef _PRINT_H_
#define _PRINT_H_

/* #includes ================================================================ */
#include "data.h"
#include "linkedlist.h"

/* function prototypes ====================================================== */
void print_footpath_segment(FILE *f, footpath_segment_t *fp);
void print_list(FILE *f, list_t *list);
void print_distinct_list(FILE *f, int col, list_t *list);
void print_array(FILE *f, array_t *A);
void print_grade1in(FILE *f, list_t *list);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */