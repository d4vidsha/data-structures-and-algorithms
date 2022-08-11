/* =============================================================================
   Project: Assignment 1
   linkedlist.c :
            = all related to linked lists
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linkedlist.h"
#include "readcsv.h"

/*  Creates an empty linked list.
*/
list_t *create_empty_list(void) {
    list_t *list;
    list = (list_t *)malloc(sizeof(*list));
    assert(list);
    list->head = list->foot = NULL;
    return list;
}

/*  Checks if list is empty.
*/
int is_empty_list(list_t *list) {
    assert(list);
    return list->head == NULL;
}

/*  Free the list by freeing all nodes and its contents.
*/
void free_list(list_t *list) {
    node_t *curr, *prev;
    assert(list);
    curr = list->head;
    while (curr) {
        prev = curr;
        curr = curr->next;
        free(prev->fp);
        free(prev);
    }
    free(list);
}

/*  Prepend to the list i.e. add to head of linked list.
*/
list_t *prepend(list_t *list, footpath_segment_t *fp) {
    node_t *new;
    assert(list);
    new = (node_t *)malloc(sizeof(*new));
    assert(new);
    new->fp = fp;
    new->next = list->head;
    list->head = new;
    if (list->foot == NULL) {
        /* this is the first insert into list */
        list->foot = new;
    }
    return list;
}

/*  Append to the list i.e. add to foot of linked list.
*/
list_t *append(list_t *list, footpath_segment_t *fp) {
    node_t *new;
    assert(list);
    new = (node_t *)malloc(sizeof(*new));
    assert(new);
    new->fp = fp;
    new->next = NULL;
    if (list->foot == NULL) {
        /* this is the first insert into list */
        list->head = list->foot = new;
    } else {
        list->foot->next = new;
        list->foot = new;
    }
    return list;
}

/*  Get the linked list length.
*/
int list_len(list_t *list) {
    assert(list);
    int len = 0;
    node_t *curr;
    curr = list->head;
    while (curr) {
        len++;
        curr = curr->next;
    }
    return len;
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
        fprintf(f, "deltaz: %.2lf || ", curr->fp->deltaz);
        fprintf(f, "distance: %.2lf || ", curr->fp->distance);
        fprintf(f, "grade1in: %.1lf || ", curr->fp->grade1in);
        fprintf(f, "mcc_id: %d || ", curr->fp->mcc_id);
        fprintf(f, "mccid_int: %d || ", curr->fp->mccid_int);
        fprintf(f, "rlmax: %.2lf || ", curr->fp->rlmax);
        fprintf(f, "rlmin: %.2lf || ", curr->fp->rlmin);
        fprintf(f, "segside: %s || ", curr->fp->segside);
        fprintf(f, "statusid: %d || ", curr->fp->statusid);
        fprintf(f, "streetid: %d || ", curr->fp->streetid);
        fprintf(f, "street_group: %d || ", curr->fp->street_group);
        fprintf(f, "start_lat: %.8lf || ", curr->fp->start_lat);
        fprintf(f, "start_lon: %.8lf || ", curr->fp->start_lon);
        fprintf(f, "end_lat: %.8lf || ", curr->fp->end_lat);
        fprintf(f, "end_lon: %.8lf || ", curr->fp->end_lon);
        fprintf(f, "\n");
        curr = curr->next;
    }
}

/* Provided a file output `f`, print the list in the specified format.
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

/*  Converts linked list to a normal `node_t` array.
*/
node_t **convert_to_array(list_t *list) {
    assert(list);
    node_t **A;
    A = (node_t **)malloc(sizeof(**A) * list_len(list));
    assert(A);
    node_t *curr;
    curr = list->head;
    int i = 0;
    while (curr) {
        A[i] = curr;
        curr = curr->next;
        i++;
    }
    return A;
}

/* =============================================================================
   Written by David Sha.
   - Implementation of linked list structs inspired by Artem Polyvyanyy from
     ass2-soln-2020.c.
   - Implementation of linked list functions inspired by Alistair Moffat
     from "Programming, Problem Solving, and Abstraction with C".
============================================================================= */