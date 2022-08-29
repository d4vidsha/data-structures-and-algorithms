/* =============================================================================
   Project: Assignment 2 (imported from Assignment 1)
   array.h :
            = all related to arrays
============================================================================= */
#ifndef _ARRAY_H_
#define _ARRAY_H_

/* #includes ================================================================ */
#include "data.h"

/* structures =============================================================== */
typedef struct array array_t;
struct array {
    footpath_segment_t **A;     // array of footpath segments
    int size;                   // current array size
    int n;                      // current number of elements
};

/* function prototypes ====================================================== */
array_t *create_array();
void free_array(array_t *A);
void shrink_array(array_t *A);
void ensure_insert_to_array(array_t *A);
void append_to_array(array_t *A, footpath_segment_t *fp);
void print_array(FILE *f, array_t *A);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */