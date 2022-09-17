#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "ll.h"

queue_t *create_queue() {
    queue_t *new;
    new = (queue_t *)malloc(sizeof(*new));
    assert(new);
    new->head = NULL;
    new->foot = NULL;
    new->num = 0;
    return new;
}

qnode_t *create_qnode(struct linkedList *list) {
    qnode_t *new;
    new = (qnode_t *)malloc(sizeof(*new));
    assert(new);
    new->list = list;
    new->next = NULL;
    return new;
}

void enqueue(queue_t *q, struct linkedList *list) {
    assert(q && list);
    
    // create queue node
    qnode_t *qn = create_qnode(list);

    // append to queue
    if (q->head == NULL && q->foot == NULL) {
        q->head = qn;
    } else {
        q->foot->next = qn;
    }
    q->foot = qn;
    q->num++;
}

struct linkedList *dequeue(queue_t *q) {
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
    
    struct linkedList *res = head->list;
    free(head);
    q->num--;
    return res;
}
