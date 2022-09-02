/* =============================================================================
   Project: Assignment 2 (altered from Assignment 1)
   linkedlist.c :
            = all related to linked lists for the `footpath_segment_t` datatype
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linkedlist.h"
#include "readcsv.h"
#include "array.h"
#include "quicksort.h"

/*  Creates an empty linked list.
*/
list_t *create_empty_list() {
    list_t *list;
    list = (list_t *)malloc(sizeof(*list));
    assert(list);
    list->head = list->foot = NULL;
    return list;
}

/*  Create a linked list given the head and foot.
*/
list_t *create_list(node_t *head, node_t *foot) {
    assert(head && foot);
    list_t *new = create_empty_list();
    new->head = head;
    new->foot = foot;
    return new;
}

/*  UNUSED FUNCTION IN IMPLEMENTATION
    Checks if list is empty.
*/
int is_empty_list(list_t *list) {
    assert(list);
    return list->head == NULL;
}

/*  Free the list by freeing all nodes and its contents.
*/
void free_list(int type, list_t *list) {
    assert(list);
    node_t *curr, *prev;
    curr = list->head;
    while (curr) {
        prev = curr;
        curr = curr->next;
        if (type == HOLLOW) {
            // do nothing
        } else if (type == NOT_HOLLOW) {
            free(prev->fp);
        } else {
            exit_failure_type(type);
        }
        free(prev);
    }
    free(list);
}

/*  UNUSED FUNCTION IN IMPLEMENTATION
    Prepend to the list i.e. add to head of linked list.
*/
list_t *prepend(list_t *list, footpath_segment_t *fp) {
    assert(list);
    assert(fp);
    node_t *new;
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
list_t *append(int type, list_t *list, footpath_segment_t *fp) {
    assert(list);
    assert(fp);
    node_t *new;
    new = (node_t *)malloc(sizeof(*new));
    assert(new);
    if (type == HOLLOW) {
        new->fp = fp;
    } else if (type == NOT_HOLLOW) {
        new->fp = footpath_segment_cpy(fp);
    } else {
        exit_failure_type(type);
    }
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
    assert(list);
    footpath_segment_t *fp;
    int c;
    while ((c = fgetc(f)) != EOF) {
        ungetc(c, f);
        fp = footpath_read_line(f);
        // `HOLLOW` here refers to adding the `fp` as a pointer to the list
        // `NOT_HOLLOW` would duplicate `fp` which we don't need
        list = append(HOLLOW, list, fp);
    }
}

/*  Print the footpath segment in a specific format into the provided 
    file `f`.
*/
void print_footpath_segment(FILE *f, footpath_segment_t *fp) {
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

/*  Converts linked list to a normal `node_t` array. Also indirectly returns
    the buddy variable of associated array.
*/
array_t *convert_to_array(int type, list_t *list) {
    assert(list);
    array_t *A = create_array();
    node_t *curr;
    curr = list->head;
    while (curr) {
        append_to_array(type, A, curr->fp);
        curr = curr->next;
    }
    shrink_array(A);
    return A;
}

/* =============================================================================
   Written by David Sha.
   - Implementation of linked list structs inspired by Artem Polyvyanyy from
     ass2-soln-2020.c.
   - Implementation of linked list functions inspired by Alistair Moffat
     from "Programming, Problem Solving, and Abstraction with C".
============================================================================= */