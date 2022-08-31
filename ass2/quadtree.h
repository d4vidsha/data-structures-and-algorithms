/* =============================================================================
   Project: Assignment 2
   quadtree.h :
            = all related to quadtrees
============================================================================= */
#ifndef _QUADTREE_H_
#define _QUADTREE_H_

/* #includes ================================================================ */
#include "data.h"
#include "linkedlist.h"

/* structures =============================================================== */
// point in 2D where `x` is longitude and `y` is latitude
typedef struct point2D point2D_t;
struct point2D {
    long double x;
    long double y;
};

// rectangle region is specified by bottom-left `bl` and top-right `tr` points
typedef struct rectangle2D rectangle2D_t;
struct rectangle2D {
    point2D_t *bl;
    point2D_t *tr;
};

// datapoint containing footpath segment and location of footpath segment
typedef struct datapoint datapoint_t;
struct datapoint {
    footpath_segment_t *fp;
    point2D_t *start;
    point2D_t *end;
};

// quadtree node
typedef struct qtnode qtnode_t;
struct qtnode {
    rectangle2D_t *region;
    int *colour;
    datapoint_t *datapoint;
    qtnode_t **quadrants;
};

/* function prototypes ====================================================== */
point2D_t *create_point(long double x, long double y);
void free_point(point2D_t *p);
rectangle2D_t *create_rectangle(point2D_t *bl, point2D_t *tr);
void free_rectangle(rectangle2D_t *r);
void free_rectangles(rectangle2D_t **A, int n);
qtnode_t *create_blank_qtnode(rectangle2D_t *r);
qtnode_t **enum_quadrants(rectangle2D_t *r);
qtnode_t *create_quadtree(list_t *list, rectangle2D_t *r);
void free_quadtree(qtnode_t *root);
int in_rectangle(point2D_t *p, rectangle2D_t *r);
int rectangle_overlap(rectangle2D_t *r1, rectangle2D_t *r2);
rectangle2D_t **partition_rectangle(rectangle2D_t *r);
int determine_quadrant(point2D_t *p, rectangle2D_t *r);
point2D_t *create_midpoint(rectangle2D_t *r);
void add_point(qtnode_t *node, datapoint_t *dp);
void attach_datapoint_to_qtnode(datapoint_t *dp, qtnode_t *node);
int is_valid_colour(int colour);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */