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
void print_point(point2D_t *p, char *label);
void print_rectangle(rectangle2D_t *r);
void print_datapoint(datapoint_t *dp);
void print_qtnode(qtnode_t *node);
void print_quadrants(qtnode_t **A);
void print_dpll(FILE *f, dpll_t *list);
void print_direction(int direction);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */