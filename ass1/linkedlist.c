/* =============================================================================
   Project: dict1
   linkedlist.c :
            = all related to linked lists
============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "data.h"

struct node {
    footpath_segment_t *fp;
    node_t *next;
};

struct linkedlist {
    node_t *head;
    node_t *tail;
};



/* =============================================================================
   Written by David Sha.
   - Implementation of a linked list inspired by Artem Polyvyanyy from
     ass2-soln-2020.c.
============================================================================= */