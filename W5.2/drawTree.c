#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "gtk.h"

/* Calculate the number of spaces which need to appear before and after the 
    data point at a given depth to allow a single character to occur in all 
    children below it. */
int spacesAtDepth(int depth);

/* Calculate the depth to the deepest child of a given node. */
int countDepth(struct bst *parent);

/* Calculate the number of nodes in the tree. */
int nodesInTree(struct bst *node){
    if(! node){
        return 0;
    }
    /* We have a node here! */
    int current = 1;
    /* Add nodes in left subtree */
    current += nodesInTree(node->left);
    /* Add nodes in right subtree */
    current += nodesInTree(node->right);
    return current;
}

void addSubtree(int *sources, int *destinations, int *filledEdges, int *usedNodes, 
    int parent, struct bst *subTree);

void setValues(int *values, int *currentVal, struct bst *parent);

/* Draws the tree. You will need to change this if your bst uses different names. */
/* You needn't understand how this works, but you're welcome to try. */
void drawTreeGTK(struct bst *parent){
    if(!parent){
        /* Done, no tree to print. */
        return;
    }

    /* Node count */
    int numNodes = nodesInTree(parent);

    /* Exactly one edge to parent for all but parent. */
    int numEdges = numNodes - 1;
    int *sources = (int *) malloc(sizeof(int)*numEdges);
    assert(sources || numEdges == 0);
    int *destinations = (int *) malloc(sizeof(int)*numEdges);
    assert(destinations || numEdges == 0);
    int *values = (int *) malloc(sizeof(int)*numNodes);
    int currentVal = 0;
    setValues(values, &currentVal, parent);
    int filledEdges = 0;
    int usedNodes = 1;
    
    /* Add all edges in tree to graph. */
    addSubtree(sources, destinations, &filledEdges, &usedNodes, 0, parent->left);
    addSubtree(sources, destinations, &filledEdges, &usedNodes, 0, parent->right);
    // printf("%d %d %d\n", numNodes, numEdges, filledEdges);

    /* Feed graph to GTK */
    #ifdef USE_GUI
    /* Guarded in case we don't want to link GTK. */
    setupGTKgraph(numNodes, numEdges, sources, destinations, values);

    /* Give GTK control! */
    runGTKInteraction();
    #endif

    /* Cleanup. */
    if(sources){
        free(sources);
    }
    if(destinations){
        free(destinations);
    }
    
}

struct readContext;
struct readContext {
    FILE *bstFile;
    struct bst **bst;
    int *sources;
    int *destinations;
};

/* Reads the next point. */
void readNextPoint(void *context, double x, double y);

void readNextPoint(void *context, double x, double y){
    /* Convenience pointer. */
    struct readContext *readContext = (struct readContext *) context;
    
    int inputData;
    if(fscanf(readContext->bstFile, "%d", &inputData) <= 0){
        /* Done, no tree changes to apply. */
        return;
    }
    printf("Adding %d\n", inputData);
    *(readContext->bst) = bstInsert(*(readContext->bst), inputData);

    if(!(*(readContext->bst))){
        /* Done, no tree to print. */
        return;
    }

    /* Node count */
    int numNodes = nodesInTree((*(readContext->bst)));

    /* Exactly one edge to parent for all but parent. */
    int numEdges = numNodes - 1;
    int *sources = (int *) malloc(sizeof(int)*numEdges);
    assert(sources || numEdges == 0);
    int *destinations = (int *) malloc(sizeof(int)*numEdges);
    assert(destinations || numEdges == 0);
    int *values = (int *) malloc(sizeof(int)*numNodes);
    int currentVal = 0;
    setValues(values, &currentVal, (*(readContext->bst)));
    int filledEdges = 0;
    int usedNodes = 1;
    
    /* Add all edges in tree to graph. */
    addSubtree(sources, destinations, &filledEdges, &usedNodes, 0, (*(readContext->bst))->left);
    addSubtree(sources, destinations, &filledEdges, &usedNodes, 0, (*(readContext->bst))->right);

    #ifdef USE_GUI
    /* Update graph in GTK. */
    setupGTKgraph(numNodes, numEdges, sources, destinations, values);
    #endif

    /* Cleanup. */
    if(readContext->sources){
        free(readContext->sources);
    }
    readContext->sources = sources;
    if(readContext->destinations){
        free(readContext->destinations);
    }
    readContext->destinations = destinations;
}

void drawTreeInteractiveGTK(struct bst **bst, FILE *bstFile){
    int inputData;
    struct readContext rc;
    if(fscanf(bstFile, "%d", &inputData) <= 0){
        /* Done, no tree to print. */
        return;
    }

    printf("Adding %d\n", inputData);
    *bst = bstInsert(*bst, inputData);

    /* Needs at least two nodes to draw tree. */
    if(fscanf(bstFile, "%d", &inputData) <= 0){
        /* Done, no tree to print. */
        return;
    }

    printf("Adding %d\n", inputData);
    *bst = bstInsert(*bst, inputData);

    /* Node count */
    int numNodes = nodesInTree((*bst));

    /* Exactly one edge to parent for all but parent. */
    int numEdges = numNodes - 1;
    int *sources = (int *) malloc(sizeof(int)*numEdges);
    assert(sources || numEdges == 0);
    int *destinations = (int *) malloc(sizeof(int)*numEdges);
    assert(destinations || numEdges == 0);
    int *values = (int *) malloc(sizeof(int)*numNodes);
    int currentVal = 0;
    setValues(values, &currentVal, (*bst));
    int filledEdges = 0;
    int usedNodes = 1;
    
    /* Add all edges in tree to graph. */
    addSubtree(sources, destinations, &filledEdges, &usedNodes, 0, (*bst)->left);
    addSubtree(sources, destinations, &filledEdges, &usedNodes, 0, (*bst)->right);
    // printf("%d %d %d\n", numNodes, numEdges, filledEdges);

    /* Setup context. */
    rc.sources = sources;
    rc.destinations = destinations;
    rc.bstFile = bstFile;
    rc.bst = bst;

    /* Feed graph to GTK */
    #ifdef USE_GUI
    /* Guarded in case we don't want to link GTK. */
    setupGTKgraph(numNodes, numEdges, sources, destinations, values);

    /* Setup click action. */
    setupGTKAction(&readNextPoint, (void *) &rc);

    /* Give GTK control! */
    runGTKInteraction();
    #endif

    /* Cleanup. */
    if(rc.sources){
        free(rc.sources);
    }
    if(rc.destinations){
        free(rc.destinations);
    }
}

void setValues(int *values, int *currentVal, struct bst *parent){
    if(! parent){
        return;
    }
    values[*currentVal] = parent->data;
    *currentVal = *currentVal + 1;
    setValues(values, currentVal, parent->left);
    setValues(values, currentVal, parent->right);
}

void addSubtree(int *sources, int *destinations, int *filledEdges, int *usedNodes, 
    int parent, struct bst *subTree){
    // Checking this way allows us to avoid checking for NULL every time we add the
    // subtree.
    if(!subTree){
        return;
    }
    int currentEdge = *filledEdges;
    int currentNode = *usedNodes;
    *usedNodes = *usedNodes + 1;
    sources[currentEdge] = parent;
    destinations[currentEdge] = currentNode;
    *filledEdges = *filledEdges + 1;
    // printf("parent -> current: %d -> %d\n", parent, currentNode);
    
    // Add subtrees.
    addSubtree(sources, destinations, filledEdges, usedNodes, currentNode, 
        subTree->left);
    addSubtree(sources, destinations, filledEdges, usedNodes, currentNode, 
        subTree->right);
}

/* Draws the tree. You will need to change this if your bst uses different names. */
/* You needn't understand how this works, but you're welcome to try. */
void drawTree(struct bst *parent){
    int i;
    if(!parent){
        /* Done, no tree to print. */
        return;
    }
    
    struct llqueue *currentQueue = newQueue();
    struct llqueue *nextQueue = newQueue();
    /* Used for swapping. */
    struct llqueue *tempQueue;
    /* Current node being processed */
    struct bst *current;
    
    /* The depth of the parent, used to work out where to place the value. */
    int depth = countDepth(parent);

    /* The number of spaces needed at the current level before and after each
        data value. */
    int spaces = spacesAtDepth(depth);

    
    /* Add the parent node to the queue. */
    queue(&currentQueue, parent);
    
    while(!empty(currentQueue) && depth >= 0){
        current = (struct bst *) dequeue(currentQueue);
        for(i = 0; i < spaces; i++){
            printf("  ");
        }
        if(current){
            printf("%2d",current->data);
        } else {
            printf("  ");
        }
        for(i = 0; i < spaces; i++){
            printf("  ");
        }
        /* Account for parent's space */
        printf("  ");

        /* Queue any children for next row */
        if(current && current->left){
            queue(&nextQueue, current->left);
        } else {
            /* Mark empty space so spacing stays consistent. */
            queue(&nextQueue, NULL);
        }

        if(current && current->right){
            queue(&nextQueue, current->right);
        } else {
            /* Mark empty space so spacing stays consistent. */
            queue(&nextQueue, NULL);
        }
        
        if(empty(currentQueue)){
            /* Start new row. */
            printf("\n");
            /* Update depth information. */
            depth--;
            spaces = spacesAtDepth(depth);
            
            /* Swap the new row to the current row. */
            tempQueue = currentQueue;
            currentQueue = nextQueue;
            nextQueue = tempQueue;
        }
    }
    /* If we reach depth 0, the queue may still have contents
        we must empty first. */
    while(!empty(currentQueue)){
        current = (struct bst *) dequeue(currentQueue);
    }
    if(nextQueue){
        free(nextQueue);
    }
    if(currentQueue){
        free(currentQueue);
    }
}

int countDepth(struct bst *parent){
    int leftDepth;
    int rightDepth;
    if(!parent){
        /* Here we assume a leaf node is at depth -1, other choices are possible. */
        return -1;
    }
    leftDepth = countDepth(parent->left);
    rightDepth = countDepth(parent->right);
    if(leftDepth > rightDepth){
        return leftDepth + 1;
    } else {
        return rightDepth + 1;
    }
}

int spacesAtDepth(int depth){
    int cDepth = depth;
    int result = 1;
    while(cDepth > 0){
        result = 2*result + 1;
        cDepth--;
    }
    return result;
}
