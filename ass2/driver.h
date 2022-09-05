/* =============================================================================
   Project: Assignment 2
   driver.h :
            = contains functions only used in driver
============================================================================= */
#ifndef _DRIVER_H_
#define _DRIVER_H_

/* #includes ================================================================ */
#include "quadtree.h"

/* function prototypes ====================================================== */
int num_args_match(int num_args, int argc);
void exit_failure_with_man();
rectangle2D_t *parse_rectangle(char *argv[]);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */