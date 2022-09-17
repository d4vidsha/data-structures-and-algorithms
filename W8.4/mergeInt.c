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
        qnode_t *qn1, *qn2, *qn3;
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

    // malloc space for merged
    merged = (qnode_t *)malloc(sizeof(*merged));
    assert(merged);
    merged->items = (int *)malloc(sizeof(*merged->items) * (qn1->num + qn2->num));
    assert(merged->items);
    merged->num = qn1->num + qn2->num;

    int i = 0, j = 0, k = 0;
    // merge two lists
    while (i < qn1->num && j < qn2->num) {
        if (qn1->items[i] < qn2->items[j]) {
            merged->items[k] = qn1->items[i];
            i++;
        } else {
            merged->items[k] = qn2->items[j];
            j++;
        }
        k++;
    }

    // copy remaining elements
    while (i < qn1->num) {
        merged->items[k] = qn1->items[i];
        i++;
        k++;
    }
    while (j < qn2->num) {
        merged->items[k] = qn2->items[j];
        j++;
        k++;
    }

    free(qn1->items);
    free(qn1);
    free(qn2->items);
    free(qn2);
    return merged;
}