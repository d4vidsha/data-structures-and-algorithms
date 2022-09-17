#include "ll.h"
#include "merge.h"
#include "queue.h"
#include <stdlib.h>

struct linkedList *mergeSort(struct linkedList *list){
    struct llq *queue = NULL;
	struct llq *nextQueue = NULL;
	struct linkedList *current = list;
	struct linkedList *next = NULL;
	struct linkedList *sortedList;
	struct linkedList *sortedListEnd;
	
	/* 
		Setup: Each list is disconnected into single 
		items and added to queue. 
		
		Adaptive Mergesort:
		Existing "runs" in the data are used as the first 
		units input into a bottom-up mergesort.
	*/
	while(current){
		next = current->next;
		current->next = NULL;
		queue = add(queue, current);
		current = next;
	}
	
	while(queue){
		/* Here we look at the finishing condition first. */
		current = dequeue(&queue);
		if(! queue){
			/* No more items left in the queue. */
			if(! nextQueue){
				/* No next queue either. Meaning only one item was in the 
					queue. */
				return current;
			} else {
				/* Next queue, but we also got an item from the queue, so we
					need to add the new list before we push the new queue. */
				nextQueue = add(nextQueue, current);
				queue = nextQueue;
				nextQueue = NULL;
			}
		} else {
			/* Otherwise we can get two items from the queue. */
			next = dequeue(&queue);
			/* Merge lists. */
			sortedList = NULL;
			sortedListEnd = NULL;
			while((current && next)){
				if(current->item <= next->item){
					if(!sortedList) {
						sortedList = current;
						sortedListEnd = current;
					} else {
						sortedListEnd->next = current;
						sortedListEnd = sortedListEnd->next;
					}
					current = current->next;
				} else {
					if(!sortedList) {
						sortedList = next;
						sortedListEnd = next;
					} else {
						sortedListEnd->next = next;
						sortedListEnd = sortedListEnd->next;
					}
					next = next->next;
				}
			}
			if(!current){
				/* Deal with subtle case with empty list */
				if (!sortedList){
					sortedList = next;
				} else {
					/* Add tail of next list to end of list. */
					sortedListEnd->next = next;
				}
			} else {
				if (!sortedList){
					sortedList = current;
				} else {
					/* Add tail of first list to end of list. */
					sortedListEnd->next = current;
				}
			}
			/* Add to next processing queue. */
			nextQueue = add(nextQueue, sortedList);
			/* If need be, flip the queues. */
			if(! queue){
				queue = nextQueue;
				nextQueue = NULL;
			}
		}
	}
	/* Control flow means this shouldn't be reachable. */
	return sortedList;
}
