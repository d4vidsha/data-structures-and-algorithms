#include "ll.h"

/* Bottom-up sorts the given list, the original list may
    be mangled in any way (and most likely will). */
struct linkedList *mergeSort(struct linkedList *list);

struct linkedList *merge(struct linkedList *l1, struct linkedList *l2);

int cmp(int n, int m);