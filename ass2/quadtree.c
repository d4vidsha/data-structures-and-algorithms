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

/*  Create point given an x and y coordinate.
*/
point2D_t *create_point(long double x, long double y) {
    point2D_t *new;
    new = (point2D_t *)malloc(sizeof(*new));
    assert(new);
    new->x = x;
    new->y = y;
    return new;
}

/*  Create rectangle given two points.
*/
rectangle2D_t *create_rectangle(point2D_t *bl, point2D_t *tr) {
    rectangle2D_t *new;
    new = (rectangle2D_t *)malloc(sizeof(*new));
    assert(new);
    new->bl = bl;
    new->tr = tr;
    return new;
}

/*  Create datapoint from given footpath segment `fp`.
*/
datapoint_t *create_datapoint(footpath_segment_t *fp) {
    datapoint_t *new;
    new = (datapoint_t *)malloc(sizeof(*new));
    assert(new);
    fp->
}

/*  Given a rectangle, create a blank quadtree node. A quadtree node is blank
    when (1) contains no datapoints and
         (2) colour is `WHITE`
*/
qtnode_t *create_blank_qtnode(rectangle2D_t *r) {
    qtnode_t *new;
    new = (qtnode_t *)malloc(sizeof(*new));
    assert(new);
    new->region = r;
    new->colour = WHITE;
}

/*  Create quadtree from a provided linked list.
*/
qtnode_t *create_quadtree(list_t *list, rectangle2D_t *r) {
    qtnode_t *root = create_blank_qtnode(r);

    node_t *curr;
    curr = list->head;
    while (curr) {
        curr->fp;
        add_point(root, dp);
        curr = curr->next;
    }
    
    return root;
}

/*  Given a point `p` and a rectangle `r`, return `1` if point is in
    the rectangle, and `0` otherwise.
    
    SPECIAL CASE:
    Points are within a rectangle if they are on lower and right boundary 
    but not on the top or left boundary.
*/
int in_rectangle(point2D_t *p, rectangle2D_t *r) {
    return (r->bl->x <= p->x && p->x < r->tr->x) &&
           (r->bl->y <= p->y && p->y < r->tr->y)
}

/*  Given two rectangles in any order, determine whether they overlap.
    More specifically, this analyses if any vertices of `r1` are in
    the rectangle `r2`.
    Returns `TRUE` if rectangles overlap, `FALSE` otherwise.
*/
int rectangle_overlap(rectangle2D_t *r1, rectangle2D_t *r2) {
    int condition = FALSE;

    // derive the four points of `r1`
    point2D_t *bl, *tr, *tl, *br;
    bl = r1->bl;
    tr = r1->tr;
    tl = create_point(bl->x, tr->y);
    br = create_point(tr->x, bl->y);

    // check if any of those points in `r2`
    if (in_rectangle(bl, r2) || in_rectangle(tr, r2) ||
        in_rectangle(tl, r2) || in_rectangle(br, r2)) {
        condition = TRUE;
    }

    free(tl);
    free(br);
    return condition;
}

/*  Given a point `p` and rectangle `r`, return the quadrant of the
    rectangle that the point lies in.
*/
qtnode_t *determine_quadrant(point2D_t *p, rectangle2D_t *r) {

}

void add_point(qtnode_t *qt, datapoint_t *dp) {

}

/* =============================================================================
   Written by David Sha.
============================================================================= */