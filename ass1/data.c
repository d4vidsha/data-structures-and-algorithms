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
    Returns the pointer to malloc'd `fp` or if unsuccessful returns `NULL`.
*/
footpath_segment_t *footpath_read_line(FILE *f) {
    footpath_segment_t *fp = NULL;
    
    int footpath_id;
    char address[MAX_STR_LEN + NULLBYTE];
    char clue_sa[MAX_STR_LEN + NULLBYTE];
    char asset_type[MAX_STR_LEN + NULLBYTE];
    double deltaz;
    // double distance;
    // double grade1in;
    // int mcc_id;
    // int mccid_int;
    // double rlmax;
    // double rlmin;
    // char segside[MAX_STR_LEN + NULLBYTE];
    // int statusid;
    // int streetid;
    // int street_group;
    // double start_lat;
    // double start_lon;
    // double end_lat;
    // double end_lon;

    int read_fields = 0;

    // read_fields = fscanf(f, "%d,%[^,],%[^,],%[^,],%lf,%lf,%lf,%d.0,%d.0,%lf,%lf,%[^,],%d.0,%d.0,%d.0,%lf,%lf,%lf,%lf\n", 
    //                &footpath_id, address, clue_sa, asset_type,
    //                &deltaz, &distance, &grade1in, &mcc_id,
    //                &mccid_int, &rlmax, &rlmin, segside,
    //                &statusid, &streetid, &street_group, &start_lat,
    //                &start_lon, &end_lat, &end_lon);

    // implement a way to read in fields
    footpath_id = get_int(f);
    get_str(f, address);
    get_str(f, clue_sa);
    get_str(f, asset_type);
    deltaz = get_double(f);

    printf("%d || %s || %s || %s || %lf ||\n", footpath_id, address, clue_sa, asset_type, deltaz);

    if (read_fields == NUM_FIELDS) {
        fp = (footpath_segment_t *)malloc(sizeof(*fp));
        assert(fp);
        // fp->footpath_id = footpath_id;
        // strcpy(fp->address, address);
        // strcpy(fp->clue_sa, clue_sa);
        // strcpy(fp->asset_type, asset_type);
        // fp->deltaz = deltaz;
        // fp->distance = distance;
        // fp->grade1in = grade1in;
        // fp->mcc_id = mcc_id;
        // fp->mccid_int = mccid_int;
        // fp->rlmax = rlmax;
        // fp->rlmin = rlmin;
        // strcpy(fp->segside, segside);
        // fp->statusid = statusid;
        // fp->streetid = streetid;
        // fp->street_group = street_group;
        // fp->start_lat = start_lat;
        // fp->start_lon = start_lon;
        // fp->end_lat = end_lat;
        // fp->end_lon = end_lon;
    } else {
        fprintf(stderr, "ERROR: failed to scan all required fields\n");
    }
    return fp;
}

void build_list(FILE *f, list_t *list) {
    footpath_segment_t *fp;
    while ((fp = footpath_read_line(f)) != NULL) {
        printf("Read in footpath_id: %d\n", fp->footpath_id);
        list = append(list, fp);
    }
}

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