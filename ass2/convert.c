/* =============================================================================
   Project: Assignment 2
   convert.c :
            = all related to converting structures
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "convert.h"
#include "linkedlist.h"
#include "array.h"
#include "quadtree.h"

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

/*  Create a new array from the datapoint linked list. If the `type` is
    `SHALLOW`, only a shell of the array is created which points to the
    original data in the linked list. If the `type` is `DEEP`, a
    new array is created and the data is copied from the linked list.
    Returns the new array.
*/
array_t *convert_dpll_to_array(int type, dpll_t *list) {
    assert(list);
    array_t *A = create_array();
    dpnode_t *curr = list->head;
    while (curr) {
        append_to_array(type, A, curr->dp->fp);
        curr = curr->next;
    }
    shrink_array(A);
    return A;
}

/*  Given an array `A` and the type, either `SHALLOW` or `DEEP`,
    convert the array to a linked list.
*/
list_t *convert_array_to_list(int type, array_t *A) {
    assert(A);
    list_t *list = create_empty_list();
    int i;
    for (i = 0; i < A->n; i++) {
        list = append(type, list, A->A[i]);
    }
    return list;
}

/* =============================================================================
   Written by David Sha.
============================================================================= */