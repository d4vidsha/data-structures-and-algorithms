/* =============================================================================
   Project: Assignment 2
   print.c :
            = all related to printing structures
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "quicksort.h"
#include "print.h"

/*  Print the footpath segment in a specific format into the provided 
    file `f`.
*/
void print_footpath_segment(FILE *f, footpath_segment_t *fp) {
    assert(fp);
    fprintf(f, "--> ");
    fprintf(f, "footpath_id: %d || ", fp->footpath_id);
    fprintf(f, "address: %s || ", fp->address);
    fprintf(f, "clue_sa: %s || ", fp->clue_sa);
    fprintf(f, "asset_type: %s || ", fp->asset_type);
    fprintf(f, "deltaz: %.2lf || ", fp->deltaz);
    fprintf(f, "distance: %.2lf || ", fp->distance);
    fprintf(f, "grade1in: %.1lf || ", fp->grade1in);
    fprintf(f, "mcc_id: %d || ", fp->mcc_id);
    fprintf(f, "mccid_int: %d || ", fp->mccid_int);
    fprintf(f, "rlmax: %.2lf || ", fp->rlmax);
    fprintf(f, "rlmin: %.2lf || ", fp->rlmin);
    fprintf(f, "segside: %s || ", fp->segside);
    fprintf(f, "statusid: %d || ", fp->statusid);
    fprintf(f, "streetid: %d || ", fp->streetid);
    fprintf(f, "street_group: %d || ", fp->street_group);
    fprintf(f, "start_lat: %.8lf || ", fp->start_lat);
    fprintf(f, "start_lon: %.8lf || ", fp->start_lon);
    fprintf(f, "end_lat: %.8lf || ", fp->end_lat);
    fprintf(f, "end_lon: %.8lf || ", fp->end_lon);
    fprintf(f, "\n");
}

/* Provided a file output `f`, print the list in the specified format.
*/
void print_list(FILE *f, list_t *list) {
    assert(list);
    node_t *curr;
    curr = list->head;
    while (curr) {
        print_footpath_segment(f, curr->fp);
        curr = curr->next;
    }
}

/*  Given a sorted list, print the list ignoring duplicates.
*/
void print_distinct_list(FILE *f, int col, list_t *list) {
    assert(list);
    node_t *curr;
    curr = list->head;
    while (curr->next) {
        double cmp = cmp_column(col, curr->fp, curr->next->fp);
        if (cmp != 0) {
            print_footpath_segment(f, curr->fp);
        }
        curr = curr->next;
    }
    print_footpath_segment(f, curr->fp);
}

/*  UNUSED FUNCTION IN IMPLEMENTATION
    Provided a file output `f`, print the the value of `grade1in` only.
*/
void print_grade1in(FILE *f, list_t *list) {
    assert(list);
    node_t *curr;
    curr = list->head;
    while (curr) {
        fprintf(f, "--> ");
        fprintf(f, "grade1in: %lf || ", curr->fp->grade1in);
        fprintf(f, "\n");
        curr = curr->next;
    }
}

/* =============================================================================
   Written by David Sha.
   - Implementation of linked list structs inspired by Artem Polyvyanyy from
     ass2-soln-2020.c.
   - Implementation of linked list functions inspired by Alistair Moffat
     from "Programming, Problem Solving, and Abstraction with C".
============================================================================= */