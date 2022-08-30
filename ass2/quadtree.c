/* =============================================================================
   Project: Assignment 2
   quadtree.c :
            = all related to quadtrees
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quadtree.h"

/* Create point given an x and y coordinate.
*/
point2D_t *create_point(long double x, long double y) {
    point2D_t *new;
    new = (point2D_t *)malloc(sizeof(*new));
    assert(new);
    new->x = x;
    new->y = y;
    return new;
}

/* Create rectangle given two points.
*/
rectangle2D_t *create_rectangle(point2D_t *bl, point2D_t *tr) {
    rectangle2D_t *new;
    new = (rectangle2D_t *)malloc(sizeof(*new));
    assert(new);
    new->bl = bl;
    new->tr = tr;
    return new;
}

/* =============================================================================
   Written by David Sha.
============================================================================= */