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
        if (type == SHALLOW) {
            // do nothing
        } else if (type == DEEP) {
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
    assert(list && fp);
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
    assert(list && fp);
    node_t *new;
    new = (node_t *)malloc(sizeof(*new));
    assert(new);
    if (type == SHALLOW) {
        new->fp = fp;
    } else if (type == DEEP) {
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
        // `SHALLOW` here refers to adding the `fp` as a pointer to the list
        // `DEEP` would duplicate `fp` which we don't need
        list = append(SHALLOW, list, fp);
    }
}

/*  Given a sorted list, return a new list but with no duplicate
    footpath segments. The other list gets free'd. The footpath segment
    data is `SHALLOW` copied.
*/
list_t *remove_duplicates(int col, list_t *list) {
    assert(list);
    list_t *results = create_empty_list();
    node_t *curr;
    curr = list->head;
    while (curr->next) {
        double cmp = cmp_column(col, curr->fp, curr->next->fp);
        if (cmp != 0) {
            append(SHALLOW, results, curr->fp);
        }
        curr = curr->next;
    }
    append(SHALLOW, results, curr->fp);
    free_list(SHALLOW, list);
    return results;
}

/* =============================================================================
   Written by David Sha.
   - Implementation of linked list structs inspired by Artem Polyvyanyy from
     ass2-soln-2020.c.
   - Implementation of linked list functions inspired by Alistair Moffat
     from "Programming, Problem Solving, and Abstraction with C".
============================================================================= */