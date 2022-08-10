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
#include "linkedlist.h"
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

/*  Given a .csv file `f`, read all data into provided `list`.
*/
void build_list(FILE *f, list_t *list) {
    footpath_segment_t *fp;
    int c;
    while ((c = fgetc(f)) != EOF) {
        ungetc(c, f);
        fp = footpath_read_line(f);
        list = append(list, fp);
    }
}

list_t *find_addresses(char *address, list_t *list) {
    assert(list);
    list_t *new = create_empty_list();
    node_t *curr;
    curr = list->head;
    while (curr) {
        int result = strcmp(address, curr->fp->address);
        if (result == 0) {
            // addresses are exactly the same
            footpath_segment_t *fp;
            fp = (footpath_segment_t *)malloc(sizeof(*fp));
            assert(fp);
            memcpy(fp, curr->fp, sizeof(*fp));
            // fp = curr->fp;   is insufficient as only assigns pointer
            new = append(new, fp);
        }
        curr = curr->next;
    }
    return new;
}

/* Provided a file output `f`, print the list in the specified format.
*/
void print_footpath_segments(FILE *f, list_t *list) {
    assert(list);
    node_t *curr;
    curr = list->head;
    while (curr) {
        fprintf(f, "--> ");
        fprintf(f, "footpath_id: %d || ", curr->fp->footpath_id);
        fprintf(f, "address: %s || ", curr->fp->address);
        fprintf(f, "clue_sa: %s || ", curr->fp->clue_sa);
        fprintf(f, "asset_type: %s || ", curr->fp->asset_type);
        fprintf(f, "deltaz: %lf || ", curr->fp->deltaz);
        fprintf(f, "distance: %lf || ", curr->fp->distance);
        fprintf(f, "grade1in: %lf || ", curr->fp->grade1in);
        fprintf(f, "mcc_id: %d || ", curr->fp->mcc_id);
        fprintf(f, "mccid_int: %d || ", curr->fp->mccid_int);
        fprintf(f, "rlmax: %lf || ", curr->fp->rlmax);
        fprintf(f, "rlmin: %lf || ", curr->fp->rlmin);
        fprintf(f, "segside: %s || ", curr->fp->segside);
        fprintf(f, "statusid: %d || ", curr->fp->statusid);
        fprintf(f, "streetid: %d || ", curr->fp->streetid);
        fprintf(f, "street_group: %d || ", curr->fp->street_group);
        fprintf(f, "start_lat: %lf || ", curr->fp->start_lat);
        fprintf(f, "start_lon: %lf || ", curr->fp->start_lon);
        fprintf(f, "end_lat: %lf || ", curr->fp->end_lat);
        fprintf(f, "end_lon: %lf || ", curr->fp->end_lon);
        fprintf(f, "\n");
        curr = curr->next;
    }
}

/* =============================================================================
   Written by David Sha.
   - Implementation inspired by W2.6 workshop content.
============================================================================= */