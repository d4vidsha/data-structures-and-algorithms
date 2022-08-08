/* =============================================================================
   Project: dict1
   data.c :
            = all related to the data
============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include "data.h"

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

/* =============================================================================
   Written by David Sha.
============================================================================= */