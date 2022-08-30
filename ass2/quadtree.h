/* =============================================================================
   Project: Assignment 2
   quadtree.h :
            = all related to quadtrees
============================================================================= */
#ifndef _QUADTREE_H_
#define _QUADTREE_H_

/* #includes ================================================================ */
#include "data.h"

/* structures =============================================================== */
// point in 2D
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

// data point containing footpath segment and location of footpath segment
typedef struct datapoint datapoint_t;
struct datapoint {
    footpath_segment_t *fp;
    point2D_t *loc;
};

// quadtree node
typedef struct qtnode qtnode_t;
struct qtnode {
    rectangle2D_t *region;
    qtnode_t *nw;
    qtnode_t *ne;
    qtnode_t *sw;
    qtnode_t *se;
};

/* function prototypes ====================================================== */
point2D_t *create_point(long double x, long double y);
rectangle2D_t *create_rectangle(point2D_t *bl, point2D_t *tr);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */