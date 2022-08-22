#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "llqueue.h"
#include "bst.h"

struct bst {
    struct bst *left;
    struct bst *right;
    int data;
};

/* 
    The function you are to write. Takes a parent pointer (null for the root),
    and returns the tree with the child in the right position. Returns the
    item in a new tree with null left/right pointers.
*/
struct bst *bstInsert(struct bst *parent, int data){
    /* Write this function. */
    if (parent == NULL) {
        struct bst *new;
        new = (struct bst *)malloc(sizeof(*new));
        new->data = data;
        new->left = new->right = NULL;
        parent = new;
    } else if (parent->data > data) {
        parent->left = bstInsert(parent->left, data);
    } else if (parent->data <= data) {
        parent->right = bstInsert(parent->right, data);
    }

    return parent;
}

void freeTree(struct bst *parent){
    if(! parent){
        return;
    }
    /* Fill in function according to function description. */
    freeTree(parent->left);
    freeTree(parent->right);
    free(parent);
}

/* Draws the tree. You will need to change this if your bst uses different names. */
/* You needn't understand how this works, but you're welcome to try. */
#include "drawTree.c"

