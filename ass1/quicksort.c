/* =============================================================================
   Project: Assignment 1
   quicksort.c :
            = all related to quicksort
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quicksort.h"
#include "data.h"
#include "readcsv.h"

/*  Implementation of quicksort to sort linked list by `col`.
    See details of sources on the very bottom of this module.
*/
void quicksort(list_t *list, int col) {
    node_t *low = list->head;
    node_t *high = list->foot;

    // there is only one element in this list, so it's sorted
    if (low == high) {
        return;
    }
    
    // find the pivot position on linked list
    node_t *pivot = partition(low, high, col);

    // quicksort upper segment
    if (pivot != NULL && pivot != high) {
        list_t *temp = create_list(pivot->next, high);
        quicksort(temp, col);
        free(temp);
    }

    // quicksort lower segment
    if (pivot->prev != NULL && pivot->prev != high) {
        list_t *temp = create_list(low, pivot->prev);
        quicksort(temp, col);
        free(temp);
    }
}

/*  Partition the linked list. The pivot is automatically set to be
    the highest value in the linked list. Compare by `col`.
    `i` is the index of smaller element, and `j` is the traversing index.
*/
node_t *partition(node_t *low, node_t *high, int col) {
    node_t *pivot = high;
    node_t *i = low;
    node_t *j = low;
    node_t *i_next, *j_next;
    while (j != NULL && j != high) {
        double cmp = cmp_column(col, j->fp, pivot->fp);

        if (cmp < 0) {
            // j is less than pivot
            assert(i);
            assert(j);
            i_next = i->next;
            j_next = j->next;
            swap(i, j);
            i = i_next;
            j = j_next;
        } else {
            j = j->next;
        }
    }
    assert(i);
    assert(pivot);
    swap(i, pivot);

    return pivot;
}

/*  Swaps the nodes by swapping `next` and `prev`.
*/
void swap(node_t *n1, node_t *n2) {
    assert(n1 && n2);
    node_t *next, *prev;
    next = n1->next;
    prev = n1->prev;
    n1->next = n2->next;
    n1->prev = n2->prev;
    n2->next = next;
    n2->prev = prev;

    // assert(n1->next != NULL);
    // assert(n1->prev != NULL);
    // assert(n2->next != NULL);
    // assert(n2->prev != NULL);
    // if (n1->next == NULL) {
    //     next = NULL;
    // } else {
    //     next = n1->next;
    // }
    // if (n1->prev == NULL) {
    //     prev = NULL;
    // } else {
    //     prev = n1->prev;
    // }
    // if (n2->next == NULL) {
    //     n1->next = NULL;
    // } else {
    //     n1->next = n2->next;
    // }
    // if (n2->prev == NULL) {
    //     n1->prev = NULL;
    // } else {
    //     n1->prev = n2->prev;
    // }
    // if (next == NULL) {
    //     n2->next = NULL;
    // } else {
    //     n2->next = next;
    // }
    // if (prev == NULL) {
    //     n2->prev = NULL;
    // } else {
    //     n2->prev = prev;
    // }
}

/*  Given a node in linked list, find the previous node and return it.
*/
node_t *get_prev_node(node_t *start, node_t *node) {
    node_t *curr, *prev = NULL;
    curr = start;
    while (curr) {
        if (curr == node) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    return prev;
}

/*  Compare two footpath segments by the specified column index.
    Order of footpath segments matter.
    Return values are:
    - [ < 0] `n` is smaller than `m`
    - [== 0] `n` is equal to `m`
    - [ > 0] `n` is larger than `m`
*/
double cmp_column(int col, footpath_segment_t *n, footpath_segment_t *m) {
    double cmp;
    // choose what to compare
    if (col == COLUMN_INDEX_GRADE1IN) {
        cmp = cmp_grade1in(n->grade1in, m->grade1in);
    } else if (col == COLUMN_INDEX_ADDRESS) {
        cmp = cmp_address(n->address, m->address);
    } else {
        fprintf(stderr, "ERROR: no compare available for index %d\n", col);
        exit(EXIT_FAILURE);
    }
    return cmp;
}

/*  Compare grade1in. Order matters.
    Return values are:
    - [ < 0] `n` is smaller than `m`
    - [== 0] `n` is equal to `m`
    - [ > 0] `n` is larger than `m`
*/
double cmp_grade1in(double n, double m) {
    return n - m;
}

/*  Compare address. Order matters.
    Return values are:
    - [ < 0] `n` is smaller than `m`
    - [== 0] `n` is equal to `m`
    - [ > 0] `n` is larger than `m`
*/
int cmp_address(char *n, char *m) {
    return strcmp(n, m);
}

/* =============================================================================
   Written by David Sha.
   - Implementation of quicksort inspired by;
        - https://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
        - https://www.geeksforgeeks.org/quick-sort/
        - https://www.youtube.com/watch?v=Hoixgm4-P4M
============================================================================= */