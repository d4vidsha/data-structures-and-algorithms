#include "ll.h"
struct llq;

/* A simple function that appends the given list to the end
    of the queue. If the given queue is NULL, one is allocated
    with the queueHead being set to the given list, otherwise
    the existing queue is returned appended with the new item. */
struct llq *add(struct llq *oldQ, struct linkedList *list);

/* Removes head of queue from queue and returns it. Queue will
    be set to NULL if it becomes empty. */
struct linkedList *dequeue(struct llq **queue);
