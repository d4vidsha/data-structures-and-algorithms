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

/*  Prints the poin given a label/description for the point.
*/
void print_point(point2D_t *p, char *label) {
    assert(p);
    printf("%s: (%Lf, %Lf)\n", label, p->x, p->y);
}

/*  Print the rectangle.
*/
void print_rectangle(rectangle2D_t *r) {
    assert(r);
    print_point(r->bl, "r->bl");
    print_point(r->tr, "r->tr");
}

/*  Print the datapoint.
*/
void print_datapoint(datapoint_t *dp) {
    assert(dp);
    print_footpath_segment(stdout, dp->fp);
    print_point(dp->p, "dp->p");
}

/*  Print the quadtree node.
*/
void print_qtnode(qtnode_t *node) {
    assert(node);
    print_rectangle(node->r);
    if (node->dpll) {
        printf("Datapoints:\n");
        dpnode_t *curr;
        curr = node->dpll->head;
        while (curr) {
            print_datapoint(curr->dp);
            curr = curr->next;
        }
    }
}

/*  Print the quadrants of a quadtree node.
*/
void print_quadrants(qtnode_t **A) {
    assert(A);
    for (int i = 0; i < MAX_CHILD_QTNODES; i++) {
        printf("Quadrant %d:\n", i);
        print_qtnode(A[i]);
    }
}

/*  Given a file `f` and a dpll `list`, print the contents of the list
    to the file.
*/
void print_dpll(FILE *f, dpll_t *list) {
    assert(list);
    dpnode_t *curr;
    curr = list->head;
    while (curr) {
        print_footpath_segment(f, curr->dp->fp);
        curr = curr->next;
    }
}

/*  Given an integer direction, print the direction in words.
*/
void print_direction(int direction) {
    char *str = get_str_direction(direction);
    printf(" %s", str);
    free(str);
}

/* =============================================================================
   Written by David Sha.
============================================================================= */