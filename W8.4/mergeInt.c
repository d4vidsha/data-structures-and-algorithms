#include "mergeInt.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int *mergeSort(int *list, int size){    
    queue_t *q = create_queue();
    int *A;

    for (int i = 0; i < size; i++) {
        A = (int *)malloc(sizeof(*A) * 1);
        assert(A);
        A[0] = list[i];
        enqueue(q, A, 1);
    }

    while (q->num > 1) {
        qnode_t *qn1, qn2, qn3;
        qn1 = dequeue(q);
        qn2 = dequeue(q);
        qn3 = merge(qn1, qn2);
        enqueue(q, qn3->items, qn3->num);

        // for (int i = 0; i < qn->num; i++) {
        //     printf("%d ", qn->items[i]);
        // }
        // printf("\n");
    }

    int *sortedList = dequeue(q)->items;
    free(q);
    return sortedList;
}

qnode_t *merge(qnode_t *qn1, qnode_t *qn2) {
    qnode_t *merged;

    

    return merged;
}