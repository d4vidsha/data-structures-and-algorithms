/* =============================================================================
   Project: dict1
   data.c :
            = all related to the data
============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "readcsv.h"

/*  Skip header line from a .csv file `f`.
*/
void skip_header_line(FILE *f) {
    while(fgetc(f) != NEWLINE);
}

/*  Given a filename `f`, read a row into `fp` of type `footpath_segment_t`.
    Returns the pointer to malloc'd `fp`.
*/
footpath_segment_t *footpath_read_line(FILE *f) {
    footpath_segment_t *fp = NULL;
    fp = (footpath_segment_t *)malloc(sizeof(*fp));
    assert(fp);
    fp->footpath_id = get_int(f);
    get_str(f, fp->address);
    get_str(f, fp->clue_sa);
    get_str(f, fp->asset_type);
    fp->deltaz = get_double(f);
    fp->distance = get_double(f);
    fp->grade1in = get_double(f);
    fp->mcc_id = get_int(f);
    fp->mccid_int = get_int(f);
    fp->rlmax = get_double(f);
    fp->rlmin = get_double(f);
    get_str(f, fp->segside);
    fp->statusid = get_int(f);
    fp->streetid = get_int(f);
    fp->street_group = get_int(f);
    fp->start_lat = get_double(f);
    fp->start_lon = get_double(f);
    fp->end_lat = get_double(f);
    fp->end_lon = get_double(f);
    return fp;
}

/* =============================================================================
   Written by David Sha.
   - Implementation inspired by W2.6 workshop content.
============================================================================= */