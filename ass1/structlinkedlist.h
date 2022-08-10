/* =============================================================================
   Project: dict1
   structlinkedlist.h :
            = contains only the struct of the footpath_segment
============================================================================= */

#ifndef _STRUCTLINKEDLIST_H_
#define _STRUCTLINKEDLIST_H_
#include "structfootpathsegment.h"

typedef struct node node_t;
struct node {
    footpath_segment_t *fp;
    node_t *next;
};

typedef struct list list_t;
struct list {
    node_t *head;
    node_t *foot;
};

#endif

/* =============================================================================
   Written by David Sha.
============================================================================= */
