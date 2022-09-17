#ifndef QUEUE
#define QUEUE
typedef struct qnode qnode_t;
struct qnode {
    qnode_t *next;
    struct linkedList *list;
};

typedef struct queue queue_t;
struct queue {
    qnode_t *head;
    qnode_t *foot;
    int num;
};
#endif

/* Create a queue */
queue_t *create_queue();

/* Create a queue node */
qnode_t *create_qnode(struct linkedList *list);

/* Add the linked list to the queue */
void enqueue(queue_t *q, struct linkedList *list);

/* Get the first in first out linked list from the given queue */
struct linkedList *dequeue(queue_t *q);
