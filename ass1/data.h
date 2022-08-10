/* =============================================================================
   Project: dict1
   data.h :
            = all related to the data
============================================================================= */

#ifndef _DATA_H_
#define _DATA_H_

#define MAX_STR_LEN 128
#define NULLBYTE_LEN 1      // size of nullbyte
#define NEWLINE '\n'
#define NUM_FIELDS 19

typedef struct footpath_segment footpath_segment_t;
struct footpath_segment {
    int footpath_id;
    char address[MAX_STR_LEN + NULLBYTE_LEN];
    char clue_sa[MAX_STR_LEN + NULLBYTE_LEN];
    char asset_type[MAX_STR_LEN + NULLBYTE_LEN];
    double deltaz;
    double distance;
    double grade1in;
    int mcc_id;
    int mccid_int;
    double rlmax;
    double rlmin;
    char segside[MAX_STR_LEN + NULLBYTE_LEN];
    int statusid;
    int streetid;
    int street_group;
    double start_lat;
    double start_lon;
    double end_lat;
    double end_lon;
};

void skip_header_line(FILE *f);
footpath_segment_t *footpath_read_line(FILE *f);

#endif



/* =============================================================================
   Written by David Sha.
============================================================================= */