/* =============================================================================
   Project: dict1
   linkedlist.h :
            = all related to linked lists
============================================================================= */

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
#include "data.h"
#include "structfootpathsegment.h"
#include "structlinkedlist.h"

list_t *create_empty_list(void);
int is_empty_list(list_t *list);
void free_list(list_t *list);
list_t *prepend(list_t *list, footpath_segment_t *fp);
list_t *append(list_t *list, footpath_segment_t *fp);
int list_len(list_t *list);

#endif



/* =============================================================================
   Written by David Sha.
============================================================================= */