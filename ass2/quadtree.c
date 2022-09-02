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
#include "copy.h"
#include "quicksort.h"

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

/*  Frees the point.
*/
void free_point(point2D_t *p) {
    free(p);
}

/*  Create rectangle given two points. The points are copied and not
    directly pointed to by the rectangle structure. This is done to 
    make freeing simpler later on.
*/
rectangle2D_t *create_rectangle(point2D_t *bl, point2D_t *tr) {
    rectangle2D_t *new;
    new = (rectangle2D_t *)malloc(sizeof(*new));
    assert(new);
    new->bl = point_cpy(bl);
    new->tr = point_cpy(tr);
    return new;
}

/*  Frees the rectangle and it's points.
*/
void free_rectangle(rectangle2D_t *r) {
    free_point(r->bl);
    free_point(r->tr);
    free(r);
}

/*  Given an array of rectangles and its buddy variable `n`,
    free all the rectangles and the array itself.
*/
void free_rectangles(rectangle2D_t **A, int n) {
    for (int i = 0; i < n; i++) {
        free_rectangle(A[i]);
    }
    free(A);
}

/*  Create datapoint from given footpath segment `fp`.
*/
datapoint_t *create_datapoint(footpath_segment_t *fp, point2D_t *p) {
    datapoint_t *new;
    new = (datapoint_t *)malloc(sizeof(*new));
    assert(new);
    new->fp = footpath_segment_cpy(fp);
    new->p = point_cpy(p);
    return new;
}

/*  Frees the datapoint, `fp` data, and `p` point.
*/
void free_datapoint(datapoint_t *dp) {
    free(dp->fp);
    free_point(dp->p);
    free(dp);
}

/*  Given a rectangle, create a blank quadtree node. A quadtree node is blank
    when (1) contains no datapoints and
         (2) colour is `WHITE`
*/
qtnode_t *create_blank_qtnode(rectangle2D_t *r) {
    qtnode_t *new;
    new = (qtnode_t *)malloc(sizeof(*new));
    assert(new);
    new->r = r;
    new->colour = WHITE;
    new->dpll = NULL;                                                      // is this necessary?
    new->quadrants = NULL;
    return new;
}

/*  Frees the node and the associated rectangle region.
*/
void free_qtnode(qtnode_t *node) {
    free_rectangle(node->r);
    free(node);
}

/*  Enumerate quadrants by instantiating `MAX_CHILD_QTNODES` blank 
    quadtree nodes.
*/
qtnode_t **enum_quadrants(rectangle2D_t *r) {
    qtnode_t **A;
    A = (qtnode_t **)malloc(sizeof(*A) * MAX_CHILD_QTNODES);
    assert(A);
    rectangle2D_t **quadrant_rectangles = partition_rectangle(r);
    for (int i = 0; i < MAX_CHILD_QTNODES; i++) {
        A[i] = create_blank_qtnode(quadrant_rectangles[i]);
    }
    free(quadrant_rectangles);
    return A;
}

/*  Create quadtree from a provided linked list and rectangular region.
*/
qtnode_t *create_quadtree(list_t *list, rectangle2D_t *r) {
    qtnode_t *root = create_blank_qtnode(r);

    datapoint_t *dp;
    point2D_t *fpp;
    node_t *curr;
    curr = list->head;
    while (curr) {

        // add start position of footpath to quadtree
        fpp = create_point(curr->fp->start_lon, curr->fp->start_lat);
        dp = create_datapoint(curr->fp, fpp);
        free_point(fpp);
        if (in_rectangle(dp->p, root->r)) {
            add_point(root, dp);
        }

        // add end position of footpath to quadtree
        fpp = create_point(curr->fp->end_lon, curr->fp->end_lat);
        dp = create_datapoint(curr->fp, fpp);
        free_point(fpp);
        if (in_rectangle(dp->p, root->r)) {
            add_point(root, dp);
        }
        
        curr = curr->next;
    }
    
    return root;
}

/*  Frees the entire quadtree from a given `root` quadtree node. Recursively
    frees all child nodes, and then the root node.
*/
void free_quadtree(qtnode_t *parent) {
    if (parent->colour == WHITE) {
        free_qtnode(parent);
    } else if (parent->colour == BLACK) {
        free_dpll(NOT_HOLLOW, parent->dpll);
        free_qtnode(parent);
    } else if (parent->colour == GREY) {
        for (int i = 0; i < MAX_CHILD_QTNODES; i++) {
            free_quadtree(parent->quadrants[i]);
        }
        free(parent->quadrants);
        free_qtnode(parent);
    }
}

/*  Given a point `p` and a rectangle `r`, return `1` if point is in
    the rectangle, and `0` otherwise.
    
    SPECIAL CASE:
    Points are within a rectangle if they are on lower and right boundary 
    but not on the top or left boundary.
*/
int in_rectangle(point2D_t *p, rectangle2D_t *r) {
    return (r->bl->x <= p->x && p->x < r->tr->x) &&
           (r->bl->y <= p->y && p->y < r->tr->y);
}

/*  Given two rectangles in any order, determine whether they overlap.
    It is easier to check if they don't overlap, hence we check whether
    (1) one rectangle is below bottom edge of other rectangle, or
    (2) one rectangle is on left side of left edge of other rectangle

    Returns `TRUE` if rectangles overlap, `FALSE` otherwise.
    See source/inspiration at bottom of file.
*/
int rectangle_overlap(rectangle2D_t *r1, rectangle2D_t *r2) {
    return !(no_vertical_overlap(r1, r2) || no_vertical_overlap(r2, r1) ||
             no_horizontal_overlap(r1, r2) || no_horizontal_overlap(r2, r1));
}

/*  Given two rectangles `r1` and `r2`, if the bottom side of `r1` is
    greater than the top side of `r2`, return `1`. Otherwise, return `0`.
*/
int no_vertical_overlap(rectangle2D_t *r1, rectangle2D_t *r2) {
    return r1->bl->y > r2->tr->y;
}

/*  Given two rectangles `r1` and `r2`, if the left side of `r1` is greater
    the right side of `r2`, return `1`. Otherwise, return `0`.
*/
int no_horizontal_overlap(rectangle2D_t *r1, rectangle2D_t *r2) {
    return r1->bl->x > r2->tr->x;
}

/*  Given a rectangle `r`, return an array of length `MAX_CHILD_QTNODES`
    containing the inner rectangle regions. Partitions equally to four 
    rectangles.
    
    NOTE: This function should be altered alongside alterations to 
    `MAX_CHILD_QTNODES`.
*/
rectangle2D_t **partition_rectangle(rectangle2D_t *r) {
    rectangle2D_t **A;
    A = (rectangle2D_t **)malloc(sizeof(*A) * MAX_CHILD_QTNODES);
    assert(A);

    // find the midpoint for the rectangle
    point2D_t *mp = create_midpoint(r);

    // create other required points, namely left, right, top and bottom of 
    // original rectangle
    point2D_t *left, *right, *top, *bottom;
    left = create_point(r->bl->x, mp->y);
    right = create_point(r->tr->x, mp->y);
    top = create_point(mp->x, r->tr->y);
    bottom = create_point(mp->x, r->bl->y);

    // create quadrant rectangles
    A[0] = create_rectangle(r->bl, mp);
    A[1] = create_rectangle(left, top);
    A[2] = create_rectangle(mp, r->tr);
    A[3] = create_rectangle(bottom, right);

    // free everything except the returning values
    free_point(mp);
    free_point(left);
    free_point(right);
    free_point(top);
    free_point(bottom);

    return A;
}

/*  Given a point `p` and rectangle `r`, return the quadrant of the
    rectangle that the point lies in as an integer.
    `0 == SW`
    `1 == NW`
    `2 == NE`
    `3 == SE`

    NOTE: If for any reason a point lies within two quadrants, only the 
    first match will be returned in the order displayed above.
*/
int determine_quadrant(point2D_t *p, rectangle2D_t *r) {
    int result = EMPTY;

    if (is_rectangle_limit(r)) {
        fprintf(stderr, "ERROR: reached rectangle limit\n");
        exit(EXIT_FAILURE);
    }

    rectangle2D_t **quadrants = partition_rectangle(r);

    // check if point `p` in any of the quadrants
    for (int i = 0; i < MAX_CHILD_QTNODES; i++) {
        if (in_rectangle(p, quadrants[i])) {
            result = i;
            break;
        }
    }

    // ensure a result was found, or else exit program
    if (result == EMPTY) {
        fprintf(stderr, "ERROR: point not in rectangle\n");
        exit(EXIT_FAILURE);
    }

    // free only what is malloc'd in this function
    free_rectangles(quadrants, MAX_CHILD_QTNODES);

    return result;
}

/*  Given a rectangle `r`, create a new point which describes the middle of the
    rectangle.
*/
point2D_t *create_midpoint(rectangle2D_t *r) {
    long double x, y;
    x = r->bl->x + (r->tr->x - r->bl->x)/2;
    y = r->bl->y + (r->tr->y - r->bl->y)/2;
    return create_point(x, y);
}

/*  Adds datapoint `dp` to quadtree starting from a parent `node` which could
    be the root node of the quadtree. This function is recursively implemented.
*/
void add_point(qtnode_t *node, datapoint_t *dp) {
    // ensure that colours are valid
    if (!is_valid_colour(node->colour)) {
        fprintf(stderr, "ERROR: quadtree node is not a valid colour\n");
        exit(EXIT_FAILURE);
    }

    // if node is blank and point in rectangle, merge datapoint to node
    if (node->colour == WHITE) {
        if (in_rectangle(dp->p, node->r)) {
            node->dpll = create_empty_dpll();
            add_datapoint_to_qtnode(dp, node);
            if (DEBUG) {
                printf("WHITE: Datapoint added\n");
            }
        }
    } else if (node->colour == BLACK) {
        // if `dp` point is exactly the same as the filled node point,
        // append another datapoint to the node.
        if (is_same_point(dp->p, node->dpll->head->dp->p)) {
            add_datapoint_to_qtnode(dp, node);
        } else {
            // split nodes into respective quadrants
            if (DEBUG) {
                printf("BLACK: Creating quadrants\n");
            }
            node->quadrants = enum_quadrants(node->r);

            // move existing datapoints to correct quadrant node
            int quadrant = determine_quadrant(node->dpll->head->dp->p, node->r);
            if (DEBUG) {
                printf("BLACK: Moving existing list of datapoints to "
                       "quadrant %d\n", quadrant);
            }
            node->quadrants[quadrant]->dpll = node->dpll;
            node->dpll = NULL;                                                 
            
            // change colours of the two nodes edited,
            // `WHITE` node becomes `BLACK` node and 
            // `BLACK` node becomes `GREY` node
            node->quadrants[quadrant]->colour = BLACK;
            node->colour = GREY;
        }
    }

    if (node->colour == GREY) {
        // if node is an internal node, traverse further down the quadtree
        int quadrant = determine_quadrant(dp->p, node->r);
        if (DEBUG) {
            printf("GREY : Moving further down tree into quadrant "
                   "%d\n", quadrant);
        }
        add_point(node->quadrants[quadrant], dp);
    }
}

/*  Given a datapoint `dp` and a `WHITE` or `BLACK` coloured `node`, insert 
    datapoint into the node. If for any reason the colour of the node is not 
    `WHITE` or `BLACK`, the function will exit the program with an error 
    message.
*/
void add_datapoint_to_qtnode(datapoint_t *dp, qtnode_t *node) {
    if (node->colour == WHITE) {
        dpll_append(HOLLOW, node->dpll, dp);
        node->colour = BLACK;
    } else if (node->colour == BLACK) {
        dpll_append(HOLLOW, node->dpll, dp);
    } else if (node->colour == GREY) {
        fprintf(stderr, "ERROR: cannot attach datapoint to quadtree node "
                        "as the node is an internal node");
        exit(EXIT_FAILURE);
    } else {
        fprintf(stderr, "ERROR: cannot attach datapoint to quadtree node "
                        "as the node is of an unknown colour");
        exit(EXIT_FAILURE);
    }
}

/*  Given a root node of a quadtree and a point (which should ideally lie
    in the region of the root node), find the leaf node that contains this
    point and return the datapoints associated with that leaf node.
*/
dpll_t *search_quadtree(qtnode_t *root, point2D_t *p) {

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

/*  Given a root node of a quadtree and a `range` described by a rectangle,
    find and return the datapoints in this range.
*/
void range_search_quadtree(dpll_t *res, qtnode_t *root, rectangle2D_t *range) {

    if (root->colour == WHITE) {
        // do nothing
        return;

    } else if (root->colour == BLACK) {
        // add datapoints from a `qtnode` to the result list
        dpnode_t *curr = root->dpll->head;
        while (curr) {
            if (in_rectangle(curr->dp->p, range)) {
                dpll_append(HOLLOW, res, curr->dp);
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
                range_search_quadtree(res, root->quadrants[i], range);
            }
        }

    } else {
        fprintf(stderr, "ERROR: while traversing quadtree, range searching "
                        "ended\n on a leaf node with an unknown colour");
        exit(EXIT_FAILURE);
    }
}

/*  Given an integer direction, print the direction in words.
*/
void print_direction(int direction) {
    char *str = get_str_direction(direction);
    printf(" %s", str);
    free(str);
}

/*  Checks that the colour for a node is valid i.e. that it should be
    one of `WHITE`, `BLACK` or `GREY`. Returns 1 if valid, and 0 if not valid.
*/
int is_valid_colour(int colour) {
    return colour == WHITE || colour == BLACK || colour == GREY;
}

/*  Prints the poin given a label/description for the point.
*/
void print_point(point2D_t *p, char *label) {
    printf("%s: (%Lf, %Lf)\n", label, p->x, p->y);
}

/*  Print the rectangle.
*/
void print_rectangle(rectangle2D_t *r) {
    print_point(r->bl, "r->bl");
    print_point(r->tr, "r->tr");
}

/*  Print the datapoint.
*/
void print_datapoint(datapoint_t *dp) {
    print_footpath_segment(stdout, dp->fp);
    print_point(dp->p, "dp->p");
}

/*  Print the quadtree node.
*/
void print_qtnode(qtnode_t *node) {
    print_rectangle(node->r);
    if (node->dpll) {
        printf("Datapoints:\n");
        dpnode_t *curr;
        curr = node->dpll->head;
        while (curr) {
            print_datapoint(curr->dp);
            curr = curr->next;
        }
    }
}

/*  Print the quadrants of a quadtree node.
*/
void print_quadrants(qtnode_t **A) {
    for (int i = 0; i < MAX_CHILD_QTNODES; i++) {
        printf("Quadrant %d:\n", i);
        print_qtnode(A[i]);
    }
}

/*  A rectangle can only become so small before something unexpected happens.
    This function checks whether the rectangle is still of a reasonable size,
    i.e. that it does not reduce to the size of a point; no area.
*/
int is_rectangle_limit(rectangle2D_t *r) {
    return is_same_point(r->bl, r->tr);
}

/*  Given two points, check if they are the exact same two points.
    Returns `1` if they are the exact same, and `0` otherwise.
*/
int is_same_point(point2D_t *p1, point2D_t *p2) {
    return p1->x == p2->x && p1->y == p2->y;
}

/*  Creates an empty linked list of the datapoint type.
*/
dpll_t *create_empty_dpll() {
    dpll_t *list;
    list = (dpll_t *)malloc(sizeof(*list));
    assert(list);
    list->head = list->foot = NULL;
    return list;
}

/*  Creates a linked list from a given `head` and `foot`.
*/
dpll_t *create_dpll(dpnode_t *head, dpnode_t *foot) {
    assert(head && foot);
    dpll_t *new = create_empty_dpll();
    new->head = head;
    new->foot = foot;
    return new;
}

/*  Free the list by freeing all nodes and its contents. If the `dpll`
    is hollow, don't free datapoints.
*/
void free_dpll(int type, dpll_t *list) {
    assert(list);
    dpnode_t *curr, *prev;
    curr = list->head;
    while (curr) {
        prev = curr;
        curr = curr->next;
        if (type == HOLLOW) {
            // do nothing
        } else if (type == NOT_HOLLOW) {
            free_datapoint(prev->dp);
        } else {
            exit_failure_type(type);
        }
        free(prev);
    }
    free(list);
}

/*  Append `dp` to the datapoint `list` i.e. add to foot of linked list.
*/
dpll_t *dpll_append(int type, dpll_t *list, datapoint_t *dp) {
    assert(list);
    assert(dp);
    dpnode_t *new;
    new = (dpnode_t *)malloc(sizeof(*new));
    assert(new);
    if (type == HOLLOW) {
        new->dp = dp;
    } else if (type == NOT_HOLLOW) {
        new->dp = datapoint_cpy(dp);
    } else {
        exit_failure_type(type);
    }
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

/*  Given a file `f` and a dpll `list`, print the contents of the list
    to the file.
*/
void print_dpll(FILE *f, dpll_t *list) {
    assert(list);
    dpnode_t *curr;
    curr = list->head;
    while (curr) {
        print_footpath_segment(f, curr->dp->fp);
        curr = curr->next;
    }
}

/*  Given an integer between 0-3, return the direction as a string with
    two characters.
    Return values are:
    - `0 == SW`
    - `1 == NW`
    - `2 == NE`
    - `3 == SE`
*/
char *get_str_direction(int direction) {
    const char *directions[] = {SW, NW, NE, SE};
    char *str;
    str = (char *)malloc(sizeof(str) * 2 + NULLBYTE_LEN);
    assert(str);
    strcpy(str, directions[direction]);
    return str;
}

/*  Given the type which is neither `HOLLOW` nor `NOT_HOLLOW`, exit with
    a failure message.
*/
void exit_failure_type(int type) {
    fprintf(stderr, "ERROR: type unknown named %d, is either `HOLLOW` or "
                    "`NOT_HOLLOW`\n", type);
    exit(EXIT_FAILURE);
}

/* =============================================================================
   Written by David Sha.
   - Rectangle overlap logic inspired by
        https://www.geeksforgeeks.org/find-two-rectangles-overlap/
============================================================================= */