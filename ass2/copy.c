/* =============================================================================
   Project: Assignment 2 (imported from Assignment 1)
   copy.c :
            = related all to copying between structs/strings
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "copy.h"
#include "data.h"

/*  Copies specified argument to `filename` string. This includes a malloc.
    Ideally, every time this function is run, an associated `free(filename)`
    is to be included.
*/
char *filename_strcpy(char *arg) {
    int filename_len = strlen(arg) + NULLBYTE_LEN;
    char *filename = (char *)malloc(sizeof(char) * filename_len);
    assert(filename);
    strcpy(filename, arg);
    return filename;
}

/*  Copies a given `footpath_segment` struct to a new struct.
*/
footpath_segment_t *footpath_segment_cpy(footpath_segment_t *fp) {
    footpath_segment_t *new;
    new = (footpath_segment_t *)malloc(sizeof(*new));
    assert(new);
    memcpy(new, fp, sizeof(*new));
    return new;
}

/* Copies a given point struct to a new point struct.
*/
point2D_t *point_cpy(point2D_t *p) {
    point2D_t *new;
    new = (point2D_t *)malloc(sizeof(*new));
    assert(new);
    memcpy(new, p, sizeof(*new));
    return new;
}

/*  Copies a given rectangle struct to a new rectangle struct.
*/
rectangle2D_t *rectangle_cpy(rectangle2D_t *r) {
    rectangle2D_t *new;
    new = (rectangle2D_t *)malloc(sizeof(*new));
    assert(new);
    memcpy(new, r, sizeof(*new));
    new->bl = point_cpy(r->bl);
    new->tr = point_cpy(r->tr);
    return new;
}

/* =============================================================================
   Written by David Sha.
============================================================================= */