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
void quicksort(node_t *low, node_t *high, int col) {
    if (low == high) {
        return;
    }
    
    node_t *pivot = partition(low, high, col);

    // ensure pivot exists and the pivot is not the last position
    if (pivot != NULL && pivot != high) {
        quicksort(pivot->next, high, col);
    }

    // get the position one unit before the pivot, otherwise if we were to use
    // just the pivot, we would have an infinite quicksort loop
    node_t *prev = get_prev_node(low, pivot);

    if (prev != NULL && prev != high) {
        quicksort(low, prev, col);
    }
}

/*  Partition the linked list. The pivot is automatically set to be
    the highest value in the linked list. Compare by `col`.
*/
node_t *partition(node_t *low, node_t *high, int col) {

    node_t *pivot = high;
    node_t *i = low;
    node_t *j = low;
    double cmp;
    while (j != NULL && j != high) {
        
        // choose what to compare
        if (col == COLUMN_INDEX_GRADE1IN) {
            cmp = cmp_grade1in(j->fp->grade1in, pivot->fp->grade1in);
        } else if (col == COLUMN_INDEX_ADDRESS) {
            cmp = cmp_address(j->fp->address, pivot->fp->address);
        } else {
            fprintf(stderr, "ERROR: no compare available for index %d\n", col);
            exit(EXIT_FAILURE);
        }

        if (cmp < 0) {
            // j is less than pivot
            // assert(i != NULL && j != NULL);
            swap(i, j);
            // assert(i->next != NULL);
            i = i->next;
        }
        j = j->next;
    }
    // assert(i != NULL);
    swap(i, pivot);

    // return the pivot position. Note that this is `i` and not `pivot` because
    // when swapping, we are only swapping the node values and not the nodes
    // themselves
    return i;
}

/*  Swaps the values inside the nodes. Note that it does NOT swap the nodes
    themselves.
*/
void swap(node_t *n1, node_t *n2) {
    footpath_segment_t *temp;
    temp = n1->fp;
    n1->fp = n2->fp;
    n2->fp = temp;
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

/*  Compare grade1in attributes.
    Return values are:
    - [ < 0] `n` is smaller than `m`
    - [== 0] `n` is equal to `m`
    - [ > 0] `n` is larger than `m`
*/
double cmp_grade1in(double n, double m) {
    return n - m;
}

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