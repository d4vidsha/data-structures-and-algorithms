#include "dictionary_struct.h"
#include "quadTree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

enum nodeType {
    INNER = 0,
    LEAF = 1
};

enum direction {
    SW = 0,
    NW = 1,
    NE = 2,
    SE = 3
};

struct rectangle2D;
struct rectangle2D {
    long double startX;
    long double startY;
    long double endX;
    long double endY;
};

struct point2D;
struct point2D {
    double x;
    double y;
};

// A linked list of data items inserted with the same point location.
struct dataNode;
struct dataNode {
    struct dictionaryNode *data;
    struct dataNode *next;
};

struct quadTreeNode;
struct quadTreeNode {
    enum nodeType nt;
    struct dataNode *data;
    struct quadTreeNode *sw;
    struct quadTreeNode *nw;
    struct quadTreeNode *ne;
    struct quadTreeNode *se;

    struct rectangle2D bounds;
    struct point2D location;
};

struct quadTree {
    struct quadTreeNode *root;
    struct rectangle2D bounds;
    unsigned int dim;
};

/* Create a new quadTree with the given bounds. */
struct quadTree *newQuadTree(long double *pointsStart, 
    long double *pointsEnd, unsigned int dim){
    assert(dim == SUPPORTED_DIMENSIONS);
    struct quadTree *qt = (struct quadTree *) malloc(sizeof(struct quadTree));
    assert(qt);
    qt->bounds.startX = pointsStart[0];
    qt->bounds.startY = pointsStart[1];
    qt->bounds.endX = pointsEnd[0];
    qt->bounds.endY = pointsEnd[1];
    qt->root = NULL;
    qt->dim = dim;
    
    return qt;
}

/* Returns 1 if the point p is in the rectangle r. Note that
points exactly sitting on the top or left borders are considered
not in the rectangle, while points exactly sitting on the bottom
or right borders are considered in the rectangle.
*/
int inRectangle(struct point2D *p, struct rectangle2D *r);

int inRectangle(struct point2D *p, struct rectangle2D *r){
    if(p->x >= r->startX && p->x < r->endX && p->y >= r->startY && p->y < r->endY){
        return 1;
    } else {
        return 0;
    }
}

/* Returns 1 if the two rectangles intersect, 0 otherwise. */
int rectangleOverlap(struct rectangle2D *first, struct rectangle2D *second);

int rectangleOverlap(struct rectangle2D *first, struct rectangle2D *second){
    /* 
    p1--p5--p2
    |        |
    p8      p6
    |        |
    p4--p7--p3

    Overlap if:
        - All corners of rectangles are the same.
        - One of the corners is present in the other rectangle.
        - One of the midpoints of one of the sides is in the other rectangle.
    */
    if(first->startX == second->startX && first->startY == second->startY
        && first->endX == second->endX && first->endY == first->endY){
        return 1;
    }
    struct point2D f1, f2, f3, f4, f5, f6, f7, f8;
    struct point2D s1, s2, s3, s4, s5, s6, s7, s8;
    
    f1.x = first->startX;
    f1.y = first->endY;
    f2.x = first->endX;
    f2.y = first->endY;
    f3.x = first->endX;
    f3.y = first->startY;
    f4.x = first->startX;
    f4.y = first->startY;
    s1.x = second->startX;
    s1.y = second->endY;
    s2.x = second->endX;
    s2.y = second->endY;
    s3.x = second->endX;
    s3.y = second->startY;
    s4.x = second->startX;
    s4.y = second->startY;

    long double fMidX = (first->startX + first->endX) / 2;
    long double fMidY = (first->startY + first->endY) / 2;
    long double sMidX = (second->startX + second->endX) / 2;
    long double sMidY = (second->startY + second->endY) / 2;
    /* 
    p1--p5--p2
    |        |
    p8      p6
    |        |
    p4--p7--p3

    Overlap if:
        - All corners of rectangles are the same.
        - One of the corners is present in the other rectangle.
        - One of the midpoints of one of the sides is in the other rectangle.
    */
    f5.x = fMidX;
    f5.y = first->endY;
    f6.x = first->endX;
    f6.y = fMidY;
    f7.x = fMidX;
    f7.y = first->startY;
    f8.x = first->startX;
    f8.y = fMidY;
    s5.x = sMidX;
    s5.y = second->endY;
    s6.x = second->endX;
    s6.y = sMidY;
    s7.x = sMidX;
    s7.y = second->startY;
    s8.x = second->startX;
    s8.y = sMidY;

    if(inRectangle(&f1, second) || inRectangle(&f2, second) || 
        inRectangle(&f3, second) || inRectangle(&f4, second) ||
        inRectangle(&s1, first) || inRectangle(&s2, first) || 
        inRectangle(&s3, first) || inRectangle(&s4, first) ||
        inRectangle(&f5, second) || inRectangle(&f6, second) || 
        inRectangle(&f7, second) || inRectangle(&f8, second) ||
        inRectangle(&s5, first) || inRectangle(&s6, first) || 
        inRectangle(&s7, first) || inRectangle(&s8, first)){
        return 1;
    }
    return 0;
}

/* Returns a new QTNode with the given bounds with the given type. */
struct quadTreeNode *newQTNode(struct rectangle2D *bounds, enum nodeType type);

struct quadTreeNode *newQTNode(struct rectangle2D *bounds, enum nodeType type){
    struct quadTreeNode *qtNode = (struct quadTreeNode *) 
        malloc(sizeof(struct quadTreeNode));
    assert(qtNode);
    qtNode->bounds = *bounds;
    qtNode->nt = type;
    qtNode->sw = NULL;
    qtNode->nw = NULL;
    qtNode->ne = NULL;
    qtNode->se = NULL;
    qtNode->data = NULL;

    return qtNode;
}

/* Inserts the given data at the head of the list and returns the list. */
struct dataNode *insertData(struct dataNode *list, struct dictionaryNode *data);

struct dataNode *insertData(struct dataNode *list, struct dictionaryNode *data){
    struct dataNode *head = (struct dataNode *) malloc(sizeof(struct dataNode));
    assert(head);
    head->next = list;
    head->data = data;
    return head;
}

/* Divides the given bounds into four rectangles and returns the SW, NW, NE or SE 
direction which the point lies in. */
enum direction selectQuadrant(struct point2D *point, struct rectangle2D *bounds);

enum direction selectQuadrant(struct point2D *point, struct rectangle2D *bounds){
    long double xMid = (bounds->startX + bounds->endX) / 2;
    long double yMid = (bounds->startY + bounds->endY) / 2;
    if(point->x >= xMid){
        if(point->y >= yMid){
            return NE;
        } else {
            return SE;
        }
    } else {
        if(point->y >= yMid){
            return NW;
        } else {
            return SW;
        }
    }
}

/* Calculates the bounds of the given quadrant and stores them in the given 
    quadrantBounds. */
void getBounds(struct rectangle2D *bounds, enum direction quadrant, 
    struct rectangle2D *quadrantBounds);

void getBounds(struct rectangle2D *bounds, enum direction quadrant, 
    struct rectangle2D *quadrantBounds){
    long double xLow = bounds->startX;
    long double xMid = (bounds->startX + bounds->endX) / 2;
    long double xHigh = bounds->endX;
    long double yLow = bounds->startY;
    long double yMid = (bounds->startY + bounds->endY) / 2;
    long double yHigh = bounds->endY;
    /*
    yHigh+-----+------+
         | NW  |  NE  |
    yMid |-----+------|
         | SW  |  SE  |
    yLow +-----+------+
        xLow  xMid  xHigh
    */
    switch(quadrant){
        case NE:
            quadrantBounds->startX = xMid;
            quadrantBounds->endX   = xHigh;
            quadrantBounds->startY = yMid;
            quadrantBounds->endY   = yHigh;
            break;
        case NW:
            quadrantBounds->startX = xLow;
            quadrantBounds->endX   = xMid;
            quadrantBounds->startY = yMid;
            quadrantBounds->endY   = yHigh;
            break;
        case SE:
            quadrantBounds->startX = xMid;
            quadrantBounds->endX   = xHigh;
            quadrantBounds->startY = yLow;
            quadrantBounds->endY   = yMid;
            break;
        case SW:
            quadrantBounds->startX = xLow;
            quadrantBounds->endX   = xMid;
            quadrantBounds->startY = yLow;
            quadrantBounds->endY   = yMid;
            break;
    }
}

/* Inserts the given data point into the quadTree, splitting if needed. */
void insertQuadTreeNode(struct quadTreeNode *node, 
    struct point2D *point, struct dictionaryNode *data);

void insertQuadTreeNode(struct quadTreeNode *node, 
    struct point2D *point, struct dictionaryNode *data){
    /* Initial check whether search is ready to insert. */
    if(node->nt == LEAF){
        if(point->x == node->location.x && point->y == node->location.y){
            node->data = insertData(node->data, data);
        } else {
            /* Split. */
            node->nt = INNER;
            enum direction quadrant = selectQuadrant(&node->location, &node->bounds);
            struct quadTreeNode **insertionNode = NULL;
            switch(quadrant){
                case SW:
                    insertionNode = &(node->sw);
                    break;
                case NW:
                    insertionNode = &(node->nw);
                    break;
                case NE:
                    insertionNode = &(node->ne);
                    break;
                case SE:
                    insertionNode = &(node->se);
                    break;
            }
            struct rectangle2D bounds;
            getBounds(&node->bounds, quadrant, &bounds);
            *insertionNode = newQTNode(&bounds, LEAF);
            (*insertionNode)->location = node->location;
            (*insertionNode)->data = node->data;
            // Remove current data in point region.
            node->data = NULL;
        }
    } 
    /* Node type may have changed to INNER in above block. */
    if(node->nt == INNER) {
        /* Work out which child we should traverse down. */
        enum direction quadrant = selectQuadrant(point, &node->bounds);
        struct quadTreeNode **insertionNode = NULL;
        switch(quadrant){
            case SW:
                insertionNode = &(node->sw);
                break;
            case NW:
                insertionNode = &(node->nw);
                break;
            case NE:
                insertionNode = &(node->ne);
                break;
            case SE:
                insertionNode = &(node->se);
                break;
        }
        if(! (*insertionNode)){
            struct rectangle2D bounds;
            getBounds(&node->bounds, quadrant, &bounds);
            *insertionNode = newQTNode(&bounds, LEAF);
            (*insertionNode)->data = insertData((*insertionNode)->data, data);
            (*insertionNode)->location = *point;
        } else {
            switch(quadrant){
                case SW:
                    insertQuadTreeNode((*insertionNode), point, data);
                    break;
                case NW:
                    insertQuadTreeNode((*insertionNode), point, data);
                    break;
                case NE:
                    insertQuadTreeNode((*insertionNode), point, data);
                    break;
                case SE:
                    insertQuadTreeNode((*insertionNode), point, data);
                    break;
            }
            // insertQuadTreeNode((*insertionNode), point, data);
        }
    }
}

/* Insert the given point into the given quadTree. Returns
    1 if the insertion was successful and 0 otherwise. */
int insertQuadTree(struct quadTree *qt, double *point, 
    struct dictionaryNode *data){
    /* Assume we have the tree and that the dimension matches expected. */
    assert(qt && qt->dim == SUPPORTED_DIMENSIONS);
    struct point2D p;
    p.x = point[0];
    p.y = point[1];
    
    assert(inRectangle(&p, &qt->bounds));
    if(! inRectangle(&p, &qt->bounds)){
        return 0;
    }

    /* Handle first case - in all other cases we will have a node to insert
    into and split. */
    if(! qt->root){
        qt->root = newQTNode(&qt->bounds, LEAF);
        qt->root->location = p;
        qt->root->data = insertData(qt->root->data, data);
    } else {
        insertQuadTreeNode(qt->root, &p, data);
    }
    return 1;
}

void searchPoint(struct quadTree *qt, double *point, int *stepCount, 
    int **steps, struct dictionaryNode ***results, int *resultCount){
    assert(qt && qt->dim == SUPPORTED_DIMENSIONS);
    struct point2D p;
    p.x = point[0];
    p.y = point[1];

    if(! qt->root || ! inRectangle(&p, &qt->bounds)){
        /* We're done if the point isn't in the quadtree bounds or we have
            nothing in the quadtree. */
        return;
    }

    int qtStepCount = 0;
    int *qtSteps = NULL;

    struct quadTreeNode *current = qt->root;
    
    while(current->nt != LEAF){
        enum direction quadrant = selectQuadrant(&p, &current->bounds);
        if(! qtSteps){
            qtSteps = (int *) malloc(sizeof(int) * (qtStepCount + 1));
            assert(qtSteps);
        } else {
            qtSteps = (int *) realloc(qtSteps, sizeof(int) * 
                (qtStepCount + 1));
            assert(qtSteps);
        }
        switch(quadrant){
            case SW:
                current = current->sw;
                qtSteps[qtStepCount] = DIR_SW;
                break;
            case NW:
                current = current->nw;
                qtSteps[qtStepCount] = DIR_NW;
                break;
            case NE:
                current = current->ne;
                qtSteps[qtStepCount] = DIR_NE;
                break;
            case SE:
                current = current->se;
                qtSteps[qtStepCount] = DIR_SE;
                break;
        }
        qtStepCount++;
    }
    assert(current);
    
    int qtResultCount = 0;
    // Count how many results will be returned.
    struct dataNode *dataCurrent = current->data;
    while(dataCurrent){
        qtResultCount++;
        dataCurrent = dataCurrent->next;
    }
    struct dictionaryNode **qtResults = (struct dictionaryNode **) 
        malloc(sizeof(struct dictionaryNode *) * qtResultCount);
    assert(qtResults);
    
    dataCurrent = current->data;
    int resultIndex = 0;
    while(dataCurrent){
        qtResults[resultIndex] = dataCurrent->data;
        resultIndex++;
        dataCurrent = dataCurrent->next;
    }

    *stepCount = qtStepCount;
    *steps = qtSteps;
    *results = qtResults;
    *resultCount = qtResultCount;
}

struct searchProgress;
struct searchProgress {
    int stepCount;
    int *steps;
    struct dictionaryNode **results;
    int resultCount;
    struct rectangle2D *region;
};

/* Search the node for all the matching regions until a leaf is reached. */
void qtSearchRegionNode(struct quadTreeNode *n, struct searchProgress *result);

/* Constant lookup */
enum direction quadrants[] = { SW, NW, NE, SE };

/* Returns the relevant pointer for the given direction. */
struct quadTreeNode *directionLookup(struct quadTreeNode *n, 
    enum direction quadrant);

struct quadTreeNode *directionLookup(struct quadTreeNode *n, 
    enum direction quadrant){
    switch(quadrant){
        case SW:
            return n->sw;
        case NW:
            return n->nw;
        case NE:
            return n->ne;
        case SE:
            return n->se;
    }
    assert(NULL);
    return NULL;
}

void qtSearchRegionNode(struct quadTreeNode *n, struct searchProgress *result){
    if(n->nt == LEAF){
        /* Check the point is actually in the region. */
        if(! inRectangle(&n->location, result->region)){
            /* Not in this node. */
            return;
        }
        struct dataNode *current = n->data;
        int nodeCount = 0;
        while(current){
            nodeCount++;
            current = current->next;
        }
        result->results = (struct dictionaryNode **) 
            realloc(result->results, sizeof(struct dictionaryNode *) * 
            (result->resultCount + nodeCount));
        assert(result->results);
        current = n->data;
        while(current){
            (result->results)[result->resultCount] = current->data;
            (result->resultCount)++;
            current = current->next;
        }
    } else {
        /* Node type == INNER, recurse down relevant trees. */
        for(int i = 0; i < sizeof(quadrants)/sizeof(quadrants[0]); i++){
            enum direction quadrant = quadrants[i];
            struct quadTreeNode *qNode = directionLookup(n, quadrant);
            if(qNode && rectangleOverlap(result->region, &qNode->bounds)){
                /* Add step. */
                if(! result->steps){
                    result->steps = (int *) malloc(sizeof(int) * 
                        (result->stepCount + 1));
                    assert(result->steps);
                } else {
                    result->steps = (int *) realloc(result->steps, 
                        sizeof(int) * (result->stepCount + 1));
                    assert(result->steps);
                }
                switch(quadrant){
                    case SW:
                        result->steps[result->stepCount] = DIR_SW;
                        break;
                    case NW:
                        result->steps[result->stepCount] = DIR_NW;
                        break;
                    case NE:
                        result->steps[result->stepCount] = DIR_NE;
                        break;
                    case SE:
                        result->steps[result->stepCount] = DIR_SE;
                        break;
                }
                (result->stepCount)++;
                /* Call recursively. */
                qtSearchRegionNode(qNode, result);
            }
        }
    }
}

void searchRegion(struct quadTree *qt, long double *pointStart, 
    long double *pointEnd, int *stepCount, int **steps, 
    struct dictionaryNode ***results, int *resultCount){
    assert(qt && qt->dim == SUPPORTED_DIMENSIONS);
    struct rectangle2D region;
    struct searchProgress result;
    region.startX = pointStart[0];
    region.startY = pointStart[1];
    region.endX = pointEnd[0];
    region.endY = pointEnd[1];

    result.stepCount = 0;
    result.steps = NULL;
    result.results = NULL;
    result.resultCount = 0;
    result.region = &region;

    if(qt->root && rectangleOverlap(&region, &qt->bounds)){
        qtSearchRegionNode(qt->root, &result);
    }

    *stepCount = result.stepCount;
    *steps = result.steps;
    *results = result.results;
    *resultCount = result.resultCount;
}

/* Free a given data list. */
void freeDataList(struct dataNode *n){
    if(! n){
        return;
    }
    struct dataNode *prev;
    struct dataNode *curr = n;
    while(curr){
        prev = curr;
        curr = curr->next;
        free(prev);
    }
}

/* Free a given QuadTree node and all its decendants. */
void freeQuadTreeNode(struct quadTreeNode *n);

void freeQuadTreeNode(struct quadTreeNode *n){
    if(! n){
        return;
    }
    if(n->nt == LEAF){
        if(n->data){
            freeDataList(n->data);
        }
    } else {
        if(n->se){
            freeQuadTreeNode(n->se);
        }
        if(n->sw){
            freeQuadTreeNode(n->sw);
        }
        if(n->ne){
            freeQuadTreeNode(n->ne);
        }
        if(n->nw){
            freeQuadTreeNode(n->nw);
        }
    }
    free(n);
}

/* Free the given quadTree, data inserted is not freed. */
void freeQuadTree(struct quadTree *qt){
    if(! qt){
        return;
    }
    if(qt->root){
        freeQuadTreeNode(qt->root);
    }
    free(qt);
}
