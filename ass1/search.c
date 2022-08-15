/* =============================================================================
   Project: Assignment 1
   search.h :
            = all related to searching
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "search.h"
#include "data.h"
#include "readcsv.h"

/*  Creates a new list with new nodes for address search results. 
*/
list_t *find_addresses(char *address, list_t *list) {
    assert(list);
    list_t *new = create_empty_list();
    node_t *curr;
    curr = list->head;
    
    while (curr) {
        int result = strcmp(address, curr->fp->address);
        if (result == 0) {
            // addresses are exactly the same
            footpath_segment_t *fp = footpath_segment_cpy(curr->fp);
            // fp = curr->fp;   is insufficient as only assigns pointer
            new = append(new, fp);
        }
        curr = curr->next;
    }
    return new;
}

/*  Linear search through sorted linked list and stopping when search value
    difference starts to grow bigger. The difference `diff` will be decreasing 
    up until a point before it increases again.
*/
list_t *linearsearch(double value, list_t *list) {
    assert(list);
    node_t *curr = list->head;
    double diff = fabs(value - curr->fp->grade1in);
    double prev_diff;
    double smallest_diff = diff;

    // find the smallest difference
    while (curr) {
        prev_diff = diff;
        diff = fabs(value - curr->fp->grade1in);

        if (prev_diff < diff) {
            // the sorted array elements are only getting bigger from here on
            // so stop searching
            break;
        }

        // only return the first found closest (<), if you want the last found
        // closest use (<=) instead
        if (diff < smallest_diff) {
            smallest_diff = diff;
        }

        curr = curr->next;
    }

    // find all footpath segments with the smallest difference
    list_t *result_list = create_empty_list();
    curr = list->head;
    diff = fabs(value - curr->fp->grade1in);
    while (curr) {
        prev_diff = diff;
        diff = fabs(value - curr->fp->grade1in);

        if (prev_diff < diff) {
            // the sorted array elements are only getting bigger from here on
            // so stop searching
            break;
        }

        // we are guaranteed at least one footpath segment appears
        if (diff == smallest_diff) {
            footpath_segment_t *fp = footpath_segment_cpy(curr->fp);
            result_list = append(result_list, fp);
        }

        curr = curr->next;
    }

    return result_list;
}

/*  Binary search through sorted array for matching `grade1in` values. 
    `arr_n` is the buddy variable of the sorted array.
    `res_n` is the buddy variable of the resulting array.
    Returns array of results.
*/
footpath_segment_t **binarysearch(double val, footpath_segment_t **A, 
                                        int *arr_n, int *res_n) {
    assert(A);
    footpath_segment_t **result;
    result = (footpath_segment_t **)malloc(sizeof(**result) * INIT_ARRAY_LEN);

    // find the smallest difference
    int diff = fabs(val - A[0]->grade1in);
    int smallest_diff = diff;
    for (int i = 1; i < *arr_n; i++) {
        diff = fabs(val - A[i]->grade1in);
        if (diff < smallest_diff) {
            smallest_diff = diff;
        } else if (diff > smallest_diff) {
            // values only get larger from here as this A
            // is assumed to be a sorted array, so no need
            // to update smallest difference anymore
            break;
        }
    }

    // conduct binary search on the smallest difference
    int lo, mid, hi;
    lo = 0;
    hi = *arr_n;
    for (int i = 0; i < *arr_n; i++) {
        mid = (lo + hi) / 2;

        diff = fabs(val - A[mid]->grade1in);

        if (smallest_diff == diff) {
            break;
        } else if (val > A[mid]->grade1in) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    // add to list and increment buddy variable
    (*res_n)++;
    result[0] = A[mid];
    return result;
}

/* =============================================================================
   Written by David Sha.
============================================================================= */