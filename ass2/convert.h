/* =============================================================================
   Project: Assignment 2
   convert.h :
            = all related to converting structures
============================================================================= */
#ifndef _CONVERT_H_
#define _CONVERT_H_

/* #includes ================================================================ */
#include "array.h"
#include "linkedlist.h"
#include "quadtree.h"

/* function prototypes ====================================================== */
array_t *convert_to_array(int type, list_t *list);
array_t *convert_dpll_to_array(int type, dpll_t *list);
list_t *convert_array_to_list(int type, array_t *A);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */