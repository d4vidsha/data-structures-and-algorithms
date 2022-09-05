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
    point2D_t *p;
};

// linked list node for storing datapoints
typedef struct dpnode dpnode_t;
struct dpnode {
    datapoint_t *dp;
    dpnode_t *next;
};

// linked list for storing datapoints
typedef struct dpll dpll_t;
struct dpll {
    dpnode_t *head;
    dpnode_t *foot;
};

// quadtree node
typedef struct qtnode qtnode_t;
struct qtnode {
    rectangle2D_t *r;
    int colour;
    dpll_t *dpll;
    qtnode_t **quadrants;
};

/* function prototypes ====================================================== */
// malloc/free functions
point2D_t *create_point(long double x, long double y);
void free_point(point2D_t *p);
rectangle2D_t *create_rectangle(point2D_t *bl, point2D_t *tr);
void free_rectangle(rectangle2D_t *r);
void free_rectangles(rectangle2D_t **A, int n);
datapoint_t *create_datapoint(footpath_segment_t *fp, point2D_t *p);
void free_datapoint(datapoint_t *dp);
dpll_t *create_empty_dpll();
dpll_t *create_dpll(dpnode_t *head, dpnode_t *foot);
void free_dpll(int type, dpll_t *list);
dpll_t *dpll_append(int type, dpll_t *list, datapoint_t *dp);
qtnode_t *create_blank_qtnode(rectangle2D_t *r);
void free_qtnode(qtnode_t *node);
qtnode_t *create_quadtree(list_t *list, rectangle2D_t *r);
void free_quadtree(qtnode_t *parent);

// manipulation functions
qtnode_t **enum_quadrants(rectangle2D_t *r);
int in_rectangle(point2D_t *p, rectangle2D_t *r);
int rectangle_overlap(rectangle2D_t *r1, rectangle2D_t *r2);
int no_vertical_overlap(rectangle2D_t *r1, rectangle2D_t *r2);
int no_horizontal_overlap(rectangle2D_t *r1, rectangle2D_t *r2);
rectangle2D_t **partition_rectangle(rectangle2D_t *r);
int determine_quadrant(point2D_t *p, rectangle2D_t *r);
point2D_t *create_midpoint(rectangle2D_t *r);
void add_point(qtnode_t *node, datapoint_t *dp);
void add_datapoint_to_qtnode(datapoint_t *dp, qtnode_t *node);
dpll_t *search_quadtree(qtnode_t *root, point2D_t *p);
dpll_t *range_search_quadtree(qtnode_t *root, rectangle2D_t *range);
void _range_search_quadtree(dpll_t *res, qtnode_t *root, rectangle2D_t *range);
int is_valid_colour(int colour);
int is_rectangle_limit(rectangle2D_t *r);
int is_same_point(point2D_t *p1, point2D_t *p2);
char *get_str_direction(int direction);
void exit_failure_type(int type);

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */