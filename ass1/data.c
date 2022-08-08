/* =============================================================================
   Project: dict1
   data.c :
            = all related to the data
============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "linkedlist.h"

struct footpath_segment {
    int footpath_id;
    char address[MAX_STR_LEN + NULLBYTE];
    char clue_sa[MAX_STR_LEN + NULLBYTE];
    char asset_type[MAX_STR_LEN + NULLBYTE];
    double deltaz;
    double distance;
    double grade1in;
    int mcc_id;
    int mccid_int;
    double rlmax;
    double rlmin;
    char segside[MAX_STR_LEN + NULLBYTE];
    int statusid;
    int streetid;
    int street_group;
    double start_lat;
    double start_lon;
    double end_lat;
    double end_lon;
};

/*  Skip header line from a .csv file `f`.
*/
void skip_header_line(FILE *f) {
    while(fgetc(f) != NEWLINE);
}

/*  Given a filename `f`, read a row into `fp` of type `footpath_segment_t`.
    Returns the pointer to `fp` or if unsuccessful returns `NULL`.
*/
footpath_segment_t *fp_read_line(FILE *f) {
    footpath_segment_t *fp = NULL;
    
    int fp_id;
    char addr[MAX_STR_LEN + NULLBYTE];


    if (fscanf(f, "%d, %s, %s, %s, 
                   %lf, %lf, %lf, %d, 
                   %d, %lf, %lf, %s, 
                   %d, %d, %d, %lf, 
                   %lf, %lf, %lf", fp_id, ) == NUM_FIELDS) {
        
        fp->footpath_id = fp_id;
    }
}

/* =============================================================================
   Written by David Sha.
   - Implementation inspired by W2.6 workshop content.
============================================================================= */