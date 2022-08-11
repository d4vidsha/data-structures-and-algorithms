/* =============================================================================
   Project: Assignment 1
   linkedlist.c :
            = all related to linked lists
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "linkedlist.h"
#include "readcsv.h"

/*  Creates an empty linked list.
*/
list_t *create_empty_list(void) {
    list_t *list;
    list = (list_t *)malloc(sizeof(*list));
    assert(list);
    list->head = list->foot = NULL;
    return list;
}

/*  Checks if list is empty.
*/
int is_empty_list(list_t *list) {
    assert(list);
    return list->head == NULL;
}

/*  Free the list by freeing all nodes and its contents.
*/
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

/*  Prepend to the list i.e. add to head of linked list.
*/
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

/*  Append to the list i.e. add to foot of linked list.
*/
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
    footpath_segment_t *fp;
    int c;
    while ((c = fgetc(f)) != EOF) {
        ungetc(c, f);
        fp = footpath_read_line(f);
        list = append(list, fp);
    }
}

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

/* Provided a file output `f`, print the list in the specified format.
*/
void print_footpath_segments(FILE *f, list_t *list) {
    assert(list);
    node_t *curr;
    curr = list->head;
    while (curr) {
        fprintf(f, "--> ");
        fprintf(f, "footpath_id: %d || ", curr->fp->footpath_id);
        fprintf(f, "address: %s || ", curr->fp->address);
        fprintf(f, "clue_sa: %s || ", curr->fp->clue_sa);
        fprintf(f, "asset_type: %s || ", curr->fp->asset_type);
        fprintf(f, "deltaz: %lf || ", curr->fp->deltaz);
        fprintf(f, "distance: %lf || ", curr->fp->distance);
        fprintf(f, "grade1in: %lf || ", curr->fp->grade1in);
        fprintf(f, "mcc_id: %d || ", curr->fp->mcc_id);
        fprintf(f, "mccid_int: %d || ", curr->fp->mccid_int);
        fprintf(f, "rlmax: %lf || ", curr->fp->rlmax);
        fprintf(f, "rlmin: %lf || ", curr->fp->rlmin);
        fprintf(f, "segside: %s || ", curr->fp->segside);
        fprintf(f, "statusid: %d || ", curr->fp->statusid);
        fprintf(f, "streetid: %d || ", curr->fp->streetid);
        fprintf(f, "street_group: %d || ", curr->fp->street_group);
        fprintf(f, "start_lat: %lf || ", curr->fp->start_lat);
        fprintf(f, "start_lon: %lf || ", curr->fp->start_lon);
        fprintf(f, "end_lat: %lf || ", curr->fp->end_lat);
        fprintf(f, "end_lon: %lf || ", curr->fp->end_lon);
        fprintf(f, "\n");
        curr = curr->next;
    }
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

/* Provided a file output `f`, print the list in the specified format.
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

/*  Implementation of quicksort to sort linked list by `grade1in`.
    See details of sources on the very bottom of this module.
*/
void quicksort(node_t *low, node_t *high) {
    if (low == high) {
        return;
    }
    
    node_t *pivot = partition(low, high);

    // ensure pivot exists and the pivot is not the last position
    if (pivot != NULL && pivot != high) {
        quicksort(pivot->next, high);
    }

    // get the position one unit before the pivot, otherwise if we were to use
    // just the pivot, we would have an infinite quicksort loop
    node_t *prev = get_prev_node(low, pivot);

    if (prev != NULL && prev != high) {
        quicksort(low, prev);
    }
}

/*  Partition the linked list. The pivot is automatically set to be
    the highest value in the linked list.
*/
node_t *partition(node_t *low, node_t *high) {

    node_t *pivot = high;
    node_t *i = low;
    node_t *j = low;
    while (j != NULL && j != high) {
        if (j->fp->grade1in < pivot->fp->grade1in) {
            assert(i != NULL && j != NULL);
            swap(i, j);
            assert(i->next != NULL);
            i = i->next;
        }
        j = j->next;
    }
    assert(i != NULL);
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

/*  Converts linked list to a normal `node_t` array.
*/
node_t **convert_to_array(list_t *list) {
    assert(list);
    node_t **A;
    A = (node_t **)malloc(sizeof(**A) * list_len(list));
    assert(A);
    node_t *curr;
    curr = list->head;
    int i = 0;
    while (curr) {
        A[i] = curr;
        curr = curr->next;
        i++;
    }
    return A;
}

/*  Copies a `footpath_segment` struct to a new struct.
*/
footpath_segment_t *footpath_segment_cpy(footpath_segment_t *fp) {
    footpath_segment_t *new;
    new = (footpath_segment_t *)malloc(sizeof(*new));
    assert(new);
    memcpy(new, fp, sizeof(*new));
    return new;
}

/*  Linear search through sorted linked list and stopping when search value
    starts to grow bigger. The difference `diff` will be decreasing up until
    a point before it increases again.
*/
list_t *linearsearch(double value, list_t *list) {
    assert(list);
    node_t *curr = list->head;
    node_t *closest = curr;
    double diff = fabs(value - curr->fp->grade1in);
    double prev_diff;
    double smallest_diff = diff;
    curr = curr->next;

    while (curr) {
        prev_diff = diff;
        diff = fabs(value - curr->fp->grade1in);

        if (prev_diff < diff) {
            // the sorted array elements are only getting bigger from here on
            // so stop searching
            break;
        }

        // only return the first found closest (<), if you want the last found
        // closest or if you intend on generating a list of all found closest 
        // use (<=) instead
        if (diff < smallest_diff) {
            smallest_diff = diff;
            closest = curr;
        }

        curr = curr->next;
    }

    // this guarantees one result in list of results
    list_t *result_list = create_empty_list();
    footpath_segment_t *fp = footpath_segment_cpy(closest->fp);
    result_list = append(result_list, fp);
    return result_list;
}

/* =============================================================================
   Written by David Sha.
   - Implementation of linked list structs inspired by Artem Polyvyanyy from
     ass2-soln-2020.c.
   - Implementation of linked list functions inspired by Alistair Moffat
     from "Programming, Problem Solving, and Abstraction with C".
   - Implementation of quicksort inspired by;
        - https://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
        - https://www.geeksforgeeks.org/quick-sort/
        - https://www.youtube.com/watch?v=Hoixgm4-P4M
============================================================================= */