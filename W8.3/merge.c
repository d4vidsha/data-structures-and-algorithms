#include "queue.h"
#include "ll.h"
#include "merge.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct linkedList *mergeSort(struct linkedList *list){

	/* FILL IN SETUP FOR Linked List BOTTOM-UP mergesort */
    queue_t *q = create_queue();
    struct linkedList *curr = list;
    struct linkedList *prev;
    while (curr) {
        // add linkedList to queue
        prev = curr;
        curr = curr->next;
        prev->next = NULL;
        enqueue(q, prev);
    }

    /* FILL IN loop */
    while (q->num > 1) {
        struct linkedList *l1, *l2, *l3;
        l1 = dequeue(q);
        l2 = dequeue(q);
        l3 = merge(l1, l2);
        enqueue(q, l3);
    }

	struct linkedList *sortedList = dequeue(q);
    free(q);
    return sortedList;
}

struct linkedList *merge(struct linkedList *l1, struct linkedList *l2) {
    struct linkedList *curr1, *curr2;
    struct linkedList *merged = NULL;

    curr1 = l1;
    curr2 = l2;

    // mergesort
    while (curr1 && curr2) {
        assert(curr1 && curr2);
        if (cmp(curr1->item, curr2->item) < 0) {
            merged = append(merged, curr1->item);
            struct linkedList *prev = curr1;
            curr1 = curr1->next;
            free(prev);
        } else {
            merged = append(merged, curr2->item);
            struct linkedList *prev = curr2;
            curr2 = curr2->next;
            free(prev);
        }
    }

    // add the rest
    if (curr1 != NULL) {
        merged = append(merged, curr1->item);
        struct linkedList *prev = curr1;
        curr1 = curr1->next;
        free(prev);
    }
    if (curr2 != NULL) {
        merged = append(merged, curr2->item);
        struct linkedList *prev = curr2;
        curr2 = curr2->next;
        free(prev);
    }

    return merged;
}

int cmp(int n, int m) {
    // printf("%d\n", n - m);
    return n - m;
}