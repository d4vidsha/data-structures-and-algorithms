/* =============================================================================
   Project: Assignment 2 (altered from Assignment 1)
   stage.h :
            = the stages of the project which processes queries on the fly
============================================================================= */
#ifndef _STAGE_H_
#define _STAGE_H_

/* #includes ================================================================ */
#include "quadtree.h"

/* function prototypes ====================================================== */
void stage1(FILE *out, list_t *list);
void stage2(FILE *out, list_t *list);
void stage3(FILE *out, qtnode_t *tree);
void stage4(FILE *out, qtnode_t *tree);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */