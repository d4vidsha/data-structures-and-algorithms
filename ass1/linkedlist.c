/* =============================================================================
   Project: dict1
   linkedlist.c :
            = all related to linked lists
============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"
#include "data.h"

struct footpath_segment {
    int footpath_id;
    char address[MAX_STR_LEN + NULLBYTE_LEN];
    char clue_sa[MAX_STR_LEN + NULLBYTE_LEN];
    char asset_type[MAX_STR_LEN + NULLBYTE_LEN];
    double deltaz;
    double distance;
    double grade1in;
    int mcc_id;
    int mccid_int;
    double rlmax;
    double rlmin;
    char segside[MAX_STR_LEN + NULLBYTE_LEN];
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

list_t *create_empty_list(void) {
    list_t *list;
    list = (list_t *)malloc(sizeof(*list));
    assert(list);
    list->head = list->foot = NULL;
    return list;
}

int is_empty_list(list_t *list) {
    assert(list);
    return list->head == NULL;
}

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


/* =============================================================================
   Written by David Sha.
   - Implementation of linked list structs inspired by Artem Polyvyanyy from
     ass2-soln-2020.c.
   - Implementation of linked list functions inspired by Alistair Moffat
     from "Programming, Problem Solving, and Abstraction with C".
============================================================================= */