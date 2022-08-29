/* =============================================================================
   Project: Assignment 2 (imported from Assignment 1)
   array.c :
            = all related to arrays
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "array.h"
#include "readcsv.h"

/*  Create an empty array.
*/
array_t *create_array() {
    array_t *new;
    new = (array_t *)malloc(sizeof(*new));
    assert(new);
    int size = INIT_ARRAY_SIZE;
    new->size = size;
    new->A = (footpath_segment_t **)malloc(sizeof(*(new->A)) * size);
    assert(new->A);
    new->n = 0;
    return new;
}

/*  Free the array.
*/
void free_array(array_t *A) {
    for (int i = 0; i < A->n; i++) {
        free(A->A[i]);
    }
    free(A->A);
    free(A);
}

/*  Shrink the array size to the number of elements.
*/
void shrink_array(array_t *A) {
    if (A->size != A->n) {
        // new size should at least be `INIT_ARRAY_SIZE`
        A->size = (A->n > INIT_ARRAY_SIZE) ? A->n : INIT_ARRAY_SIZE;
        A->A = (footpath_segment_t **)realloc(A->A, sizeof(*(A->A)) * A->size);
        assert(A->A);
    }
}

/*  Ensure that there is enough space for inserting into the array.
*/
void ensure_insert_to_array(array_t *A) {
    if (A->n == A->size) {
        A->size *= 2;
        A->A = (footpath_segment_t **)realloc(A->A, sizeof(*(A->A)) * A->size);
        assert(A->A);
    }
}

/*  Append footpath segment to array.
*/
void append_to_array(array_t *A, footpath_segment_t *fp) {
    ensure_insert_to_array(A);
    A->A[A->n] = fp;
    (A->n)++;
}

/*  Print the array.
*/
void print_array(FILE *f, array_t *A) {
    assert(A);
    for (int i = 0; i < A->n; i++) {
        print_footpath_segment(f, A->A[i]);
    }
}

/* =============================================================================
   Written by David Sha.
   - Implementation of array inspired by W3.9 workshop exercise
============================================================================= */