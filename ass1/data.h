/* =============================================================================
   Project: dict1
   data.h :
            = all related to the data
============================================================================= */

#ifndef _DATA_H_
#define _DATA_H_

#define MAX_STR_LEN 128
#define NULLBYTE 1      // size of nullbyte
#define NEWLINE '\n'
#define NUM_FIELDS 19

typedef struct footpath_segment footpath_segment_t;


void skip_header_line(FILE *f);
footpath_segment_t *footpath_read_line(FILE *f);

#endif



/* =============================================================================
   Written by David Sha.
============================================================================= */