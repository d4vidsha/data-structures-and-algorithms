#include <stdlib.h>
#include <assert.h>
#include "queue.h"

queue_t *create_queue() {
    queue_t *new;
    new = (queue_t *)malloc(sizeof(*new));
    assert(new);
    new->head = NULL;
    new->foot = NULL;
    new->num = 0;
    return new;
}

qnode_t *create_qnode(int *items, int num) {
    qnode_t *new;
    new = (qnode_t *)malloc(sizeof(*new));
    assert(new);
    new->items = items;
    new->num = num;
    new->next = NULL;
    return new;
}

void enqueue(queue_t *q, int *items, int num) {
    assert(q && items);
    
    // create queue node
    qnode_t *qn = create_qnode(items, num);

    // append to queue
    if (q->head == NULL && q->foot == NULL) {
        q->head = qn;
    } else {
        q->foot->next = qn;
    }
    q->foot = qn;
    q->num++;
}

qnode_t *dequeue(queue_t *q) {
    assert(q);
    // ensure there is at least one qnode to dequeue
    if (q->num <= 0) {
        exit(EXIT_FAILURE);
    }

    // pop the first queue node from queue
    qnode_t *head = q->head;
    if (q->num == 1) {
        q->head = NULL;
        q->foot = NULL;
    } else if (q->num > 1) {
        q->head = head->next;
    }
    
    q->num--;
    return head;
}
