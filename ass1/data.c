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

struct node {
    footpath_segment_t *fp;
    node_t *next;
};

struct list {
    node_t *head;
    node_t *foot;
};

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
        printf("Read in %d\n", fp->footpath_id);
        list = append(list, fp);
    }
}

/* Provided a file output `f`, print the list in the specified format.
*/
void print_list(FILE *f, list_t *list) {
    node_t *node;
    node = list->head;
    while (node) {
        fprintf(f, "%d\n", node->fp->footpath_id);
        node = node->next;
    }
}

/* =============================================================================
   Written by David Sha.
   - Implementation inspired by W2.6 workshop content.
============================================================================= */