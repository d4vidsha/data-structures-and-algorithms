#include <stdlib.h>
#include <assert.h>
#include "ll.h"

struct llq {
    struct linkedList *queueHead;
    struct llq *next;
};

struct llq *add(struct llq *oldQ, struct linkedList *list){
    if(! oldQ){
        oldQ = (struct llq *) malloc(sizeof(struct llq));
        assert(oldQ);
        oldQ->queueHead = list;
        oldQ->next = NULL;
    } else {
        oldQ->next = add(oldQ->next, list);
    }
    return oldQ;
}

struct linkedList *dequeue(struct llq **queue){
    struct linkedList *res = (*queue)->queueHead;
    struct llq *oldQ = *queue;
    
    *queue = (*queue)->next;
	/* Clean up memory we allocated. */
	free(oldQ);
	
    return res;
}
