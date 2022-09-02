/* =============================================================================
   Project: Assignment 2 (altered from Assignment 1)
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
    assert(list);
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

    // get the position one unit before the pivot, otherwise if we were to use
    // just the pivot, we would have an infinite quicksort loop. Notice that
    // using this method of getting previous node will reduce the efficiency
    // of quicksort
    node_t *prev = get_prev_node(low, pivot);

    // quicksort lower segment
    if (prev != NULL && prev != high) {
        list_t *temp = create_list(low, prev);
        quicksort(temp, col);
        free(temp);
    }
}

/*  Partition the linked list. The pivot is automatically set to be
    the highest value in the linked list. Compare by `col`.
    `i` is the index of smaller element, and `j` is the traversing index.
*/
node_t *partition(node_t *low, node_t *high, int col) {
    assert(low && high);
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
    assert(n1 && n2);
    footpath_segment_t *temp;
    temp = n1->fp;
    n1->fp = n2->fp;
    n2->fp = temp;
}

/*  Given a node in linked list, find the previous node and return it.
*/
node_t *get_prev_node(node_t *start, node_t *node) {
    assert(start && node);
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
    assert(n && m);
    double cmp;
    // choose what to compare
    if (col == COLUMN_INDEX_GRADE1IN) {
        cmp = cmp_grade1in(n->grade1in, m->grade1in);
    } else if (col == COLUMN_INDEX_ADDRESS) {
        cmp = cmp_address(n->address, m->address);
    } else if (col == COLUMN_INDEX_FPID) {
        cmp = cmp_footpath_id(n->footpath_id, m->footpath_id);
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

/*  UNUSED FUNCTION IN IMPLEMENTATION
    Compare address. Order matters.
    Return values are:
    - [ < 0] `n` is smaller than `m`
    - [== 0] `n` is equal to `m`
    - [ > 0] `n` is larger than `m`
*/
int cmp_address(char *n, char *m) {
    return strcmp(n, m);
}

/*  Compare `footpath_id`. Order matters.
    Return values are:
    - [ < 0] `n` is smaller than `m`
    - [== 0] `n` is equal to `m`
    - [ > 0] `n` is larger than `m`
*/
int cmp_footpath_id(int n, int m) {
    return n - m;
}

/*  Create a new array from the datapoint linked list. If the `type` is
    `HOLLOW`, only a shell of the array is created which points to the
    original data in the linked list. If the `type` is `NOT_HOLLOW`, a
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

/*  Given a column to sort by `col`, an array `A`, the start index `lo`,
    and the end index `hi`, sort the array using quicksort.
*/
void quicksort_array(int col, array_t *A, int lo, int hi) {
    assert(A);
    int pivot;

    // there is only one element in this list, so it's sorted
    if (lo < hi) {
        pivot = partition_array(col, A->A, lo, hi);
    } else {
        return;
    }
    quicksort_array(col, A, lo, pivot - 1);
    quicksort_array(col, A, pivot + 1, hi);
}

/*  Given a column to sort by `col`, an array `A`, the start index `lo`,
    and the end index `hi`, partition the array using quicksort.
    Returns the pivot index.
*/
int partition_array(int col, footpath_segment_t **A, int lo, int hi) {
    assert(A);
    int i, j;
    footpath_segment_t *pivot = A[hi];

    i = lo - 1;

    for (j = lo; j < hi; j++) {
        double cmp = cmp_column(col, A[j], pivot);
        if (cmp < 0) {
            i++;
            swap_elem(A, i, j);
        }
    }
    swap_elem(A, i + 1, hi);
    return i + 1;
}

/*  Swaps two elements in an array.
*/
void swap_elem(footpath_segment_t **A, int i, int j) {
    assert(A);
    footpath_segment_t *temp;
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

/* Given a column to sort by `col`, an array `A`, ensure that the array
   is sorted. If it is not sorted, print an error message and exit.
*/
void check_array_sorted(int col, array_t *A) {
    assert(A);
    int i;
    for (i = 0; i < A->n - 1; i++) {
        double cmp = cmp_column(col, A->A[i], A->A[i + 1]);
        if (cmp > 0) {
            printf("ERROR: array is not sorted at index %d suggesting "
                   "something is wrong with the sorting algorithm\n", i);
            exit(EXIT_FAILURE);
        }
    }
}

/*  Given an array `A` and the type, either `HOLLOW` or `NOT_HOLLOW`,
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
   - Implementation of quicksort inspired by;
        - https://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
        - https://www.geeksforgeeks.org/quick-sort/
        - https://www.youtube.com/watch?v=Hoixgm4-P4M
============================================================================= */