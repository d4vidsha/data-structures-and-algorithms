#ifndef QUEUE
#define QUEUE
typedef struct qnode qnode_t;
struct qnode {
    qnode_t *next;
    int *items;
    int num;
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
qnode_t *create_qnode(int *items, int num);

/* Add the linked list to the queue */
void enqueue(queue_t *q, int *items, int num);

/* Get the first in first out linked list from the given queue */
qnode_t *dequeue(queue_t *q);
