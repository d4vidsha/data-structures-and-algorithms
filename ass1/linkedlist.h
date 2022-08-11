/* =============================================================================
   Project: dict1
   linkedlist.h :
            = all related to linked lists
============================================================================= */

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
#include "data.h"

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

list_t *create_empty_list(void);
int is_empty_list(list_t *list);
void free_list(list_t *list);
list_t *prepend(list_t *list, footpath_segment_t *fp);
list_t *append(list_t *list, footpath_segment_t *fp);
int list_len(list_t *list);
void build_list(FILE *f, list_t *list);
list_t *find_addresses(char *address, list_t *list);
void print_footpath_segments(FILE *f, list_t *list);
void print_grade1in(FILE *f, list_t *list);
void quicksort(node_t *low, node_t *high);
node_t *partition(node_t *low, node_t *high);
void swap(node_t *n1, node_t *n2);
node_t **convert_to_array(list_t *list);
footpath_segment_t *footpath_segment_cpy(footpath_segment_t *fp);
list_t *linearsearch(double value, list_t *list);

#endif



/* =============================================================================
   Written by David Sha.
============================================================================= */