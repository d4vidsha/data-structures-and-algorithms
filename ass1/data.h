/* =============================================================================
   Project: dict1
   data.h :
            = all related to the data
============================================================================= */

#ifndef _DATA_H_
#define _DATA_H_
#include "linkedlist.h"

#define MAX_STR_LEN 128
#define NULLBYTE 1      // size of nullbyte
#define NEWLINE '\n'
#define NUM_FIELDS 19

typedef struct footpath_segment footpath_segment_t;
typedef struct node node_t;
typedef struct list list_t;


void skip_header_line(FILE *f);
footpath_segment_t *footpath_read_line(FILE *f);
void build_list(FILE *f, list_t *list);
list_t *find_addresses(char *address, list_t *list);
void print_footpath_segments(FILE *f, list_t *list);

#endif



/* =============================================================================
   Written by David Sha.
============================================================================= */