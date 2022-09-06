/* =============================================================================
   Project: Assignment 2 (altered from Assignment 1)
   linkedlist.h :
            = all related to linked lists for the `footpath_segment_t` datatype
============================================================================= */
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

/* #includes ================================================================ */
#include "data.h"
#include "array.h"

/* structures =============================================================== */
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

/* function prototypes ====================================================== */
list_t *create_empty_list();
list_t *create_list(node_t *head, node_t *foot);
int is_empty_list(list_t *list);
void free_list(int type, list_t *list);
list_t *prepend(list_t *list, footpath_segment_t *fp);
list_t *append(int type, list_t *list, footpath_segment_t *fp);
int list_len(list_t *list);
void build_list(FILE *f, list_t *list);
list_t *remove_duplicates(int col, list_t *list);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */