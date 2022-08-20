#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#ifdef USE_GUI
#include "gtk.h"
#endif

int main(int argc, char **argv){
    int inputData;
    struct bst *bst = NULL;
    #ifndef USE_GUI
    while(scanf("%d", &inputData) > 0){
        bst = bstInsert(bst, inputData);
    }
    #endif

    #ifdef USE_GUI

    setupGTK(&argc, &argv, "Binary Search Tree");

        #ifndef GUI_INTERACTIVE
    while(scanf("%d", &inputData) > 0){
        bst = bstInsert(bst, inputData);
    }
    drawTreeGTK(bst);
        #else
    drawTreeInteractiveGTK(&bst, stdin);
        #endif
    
    #else
    drawTree(bst);
    #endif
    
    freeTree(bst);

    return 0;
}
