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

    while (j != NULL && j != high) {
        double cmp = cmp_column(col, j->fp, pivot->fp);

        if (cmp < 0) {
            // j is less than pivot
            swap(i, j);
            i = i->next;
        }

        j = j->next;
    }
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