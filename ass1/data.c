/* =============================================================================
   Project: dict1
   data.c :
            = all related to the data
============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
footpath_segment_t *footpath_read_line(FILE *f) {
    footpath_segment_t *fp = NULL;
    
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

    if (fscanf(f, "%d, %s, %s, %s, %lf, %lf, %lf, %d, %d, %lf, %lf, %s, %d, %d, %d, %lf, %lf, %lf, %lf", 
                   &footpath_id, address, clue_sa, asset_type,
                   &deltaz, &distance, &grade1in, &mcc_id,
                   &mccid_int, &rlmax, &rlmin, segside,
                   &statusid, &streetid, &street_group, &start_lat,
                   &start_lon, &end_lat, &end_lon) == NUM_FIELDS) {
        
        fp->footpath_id = footpath_id;
        strcpy(fp->address, address);
        strcpy(fp->clue_sa, clue_sa);
        strcpy(fp->asset_type, asset_type);
        fp->deltaz = deltaz;
        fp->distance = distance;
        fp->grade1in = grade1in;
        fp->mcc_id = mcc_id;
        fp->mccid_int = mccid_int;
        fp->rlmax = rlmax;
        fp->rlmin = rlmin;
        strcpy(fp->segside, segside);
        fp->statusid = statusid;
        fp->streetid = streetid;
        fp->street_group = street_group;
        fp->start_lat = start_lat;
        fp->start_lon = start_lon;
        fp->end_lat = end_lat;
        fp->end_lon = end_lon;
    }
    return fp;
}

/* =============================================================================
   Written by David Sha.
   - Implementation inspired by W2.6 workshop content.
============================================================================= */