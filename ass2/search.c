/* =============================================================================
   Project: Assignment 2 (altered from Assignment 1)
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
            new = append(DEEP, new, curr->fp);
        }
        curr = curr->next;
    }
    return new;
}

/*  UNUSED FUNCTION IN IMPLEMENTATION
    Linear search through sorted linked list and stopping when search value
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
            result_list = append(DEEP, result_list, curr->fp);
        }

        curr = curr->next;
    }

    return result_list;
}

/*  Binary search through sorted array for matching `grade1in` values. 
    Returns array of results. Note that this implementation is not
    complete as there is currently no way to return multiple results.
    However, `linearsearch` function achieves returning multiple results
    and should be used instead if that is what you want.
*/
array_t *binarysearch(double val, array_t *A) {
    assert(A);
    array_t *results = create_array();

    // find the smallest difference
    double diff = fabs(val - A->A[0]->grade1in);
    double smallest_diff = diff;
    for (int i = 1; i < A->n; i++) {
        diff = fabs(val - A->A[i]->grade1in);
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
    hi = A->n;
    for (int i = 0; i < A->n; i++) {
        mid = (lo + hi) / 2;

        diff = fabs(val - A->A[mid]->grade1in);

        if (smallest_diff == diff) {
            // reached section of array where value closest matches
            // the array elements
            append_to_array(DEEP, results, A->A[mid]);
            break;
        } else if (val > A->A[mid]->grade1in) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return results;
}

/*  Given a root node of a quadtree and a point (which should ideally lie
    in the region of the root node), find the leaf node that contains this
    point and return the datapoints associated with that leaf node.
*/
dpll_t *search_quadtree(qtnode_t *root, point2D_t *p) {
    assert(root && p);

    // ensure the search point is within the root node's rectangle
    if (!in_rectangle(p, root->r)) {
        fprintf(stderr, "ERROR: search point not in root node's rectangle\n");
        exit(EXIT_FAILURE);
    }

    // traverse down the quadtree until a leaf node is found
    qtnode_t *curr = root;
    int quadrant;
    while (curr->colour == GREY) {
        quadrant = determine_quadrant(p, curr->r);
        curr = curr->quadrants[quadrant];
        print_direction(quadrant);
    }
    printf("\n");

    // if `WHITE`, it will return `NULL` as specified by 
    // `create_blank_qtnode()` and if `BLACK`, it will return
    // the linked list of datapoints
    if (curr->colour == WHITE) {
        return NULL;
    } else if (curr->colour == BLACK) {
        return curr->dpll;
    } else {
        fprintf(stderr, "ERROR: while traversing quadtree, searching ended\n"
                        "on a leaf node with an unknown colour");
        exit(EXIT_FAILURE);
    }
}

/*  Given a root node of a quadtree and a rectangule range, find all the 
    datapoints that lie within the rectangle range and return them in a 
    datapoint linked list.
*/
dpll_t *range_search_quadtree(qtnode_t *root, rectangle2D_t *range) {
    dpll_t *results = create_empty_dpll();
    _range_search_quadtree(results, root, range);
    return results;
}

/*  Given a root node of a quadtree and a `range` described by a rectangle,
    find and return the datapoints in this range to `res`. This is a 
    recursive helper function, hence the underscore at the start of the
    function name.
*/
void _range_search_quadtree(dpll_t *res, qtnode_t *root, rectangle2D_t *range) {
    assert(res && root && range);

    if (root->colour == WHITE) {
        // do nothing
        return;

    } else if (root->colour == BLACK) {
        // add datapoints from a `qtnode` to the result list
        dpnode_t *curr = root->dpll->head;
        while (curr) {
            if (in_rectangle(curr->dp->p, range)) {
                dpll_append(SHALLOW, res, curr->dp);
            }
            curr = curr->next;
        }

    } else if (root->colour == GREY) {
        // scanning through child nodes
        for (int i = 0; i < MAX_CHILD_QTNODES; i++) {
            if (rectangle_overlap(root->quadrants[i]->r, range) 
                    && root->quadrants[i]->colour != WHITE) {
                // rectangle overlap
                print_direction(i);
                _range_search_quadtree(res, root->quadrants[i], range);
            }
        }

    } else {
        fprintf(stderr, "ERROR: while traversing quadtree, range searching "
                        "ended\n on a leaf node with an unknown colour");
        exit(EXIT_FAILURE);
    }
}

/* =============================================================================
   Written by David Sha.
   - Binary search inspired by https://www.geeksforgeeks.org/binary-search/
============================================================================= */