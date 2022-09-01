/* QUICKSORT UNFINISHED */

/*  Implementation of quicksort to sort linked list by `footpath_id`.
    Similar `quicksort()` function but adapted for datapoint linked list
    type `dpll_t`.
*/
void quicksort_dpll(dpll_t *list) {
    dpnode_t *low = list->head;
    dpnode_t *high = list->foot;

    // there is only one element in this list, so it's sorted
    if (low == high) {
        return;
    }
    
    // find the pivot position on linked list
    dpnode_t *pivot = partition_dpll(low, high, col);

    // quicksort upper segment
    if (pivot != NULL && pivot != high) {
        list_t *temp = create_dpll(pivot->next, high);
        quicksort_dpll(temp, col);
        free(temp);
    }

    // get the position one unit before the pivot, otherwise if we were to use
    // just the pivot, we would have an infinite quicksort loop. Notice that
    // using this method of getting previous node will reduce the efficiency
    // of quicksort
    dpnode_t *prev = get_prev_dpnode(low, pivot);

    // quicksort lower segment
    if (prev != NULL && prev != high) {
        list_t *temp = create_dpll(low, prev);
        quicksort_dpll(temp);
        free(temp);
    }
}

/*  Partition the `dpll` linked list. The pivot is automatically set to be
    the highest value in the linked list. Compare by footpath_id.
    `i` is the index of smaller element, and `j` is the traversing index.
*/
dpnode_t *partition_dpll(dpnode_t *low, dpnode_t *high) {
    dpnode_t *pivot = high;
    dpnode_t *i = low;
    dpnode_t *j = low;

    while (j != NULL && j != high) {
        double cmp = cmp_footpath_id(j->dp->fp, pivot->dp->fp);

        if (cmp < 0) {
            // j is less than pivot
            swap_dpnodes(i, j);
            i = i->next;
        }

        j = j->next;
    }
    swap_dpnodes(i, pivot);

    // return the pivot position. Note that this is `i` and not `pivot` because
    // when swapping, we are only swapping the node values and not the nodes
    // themselves
    return i;
}

/*  Swaps the values inside the nodes. Note that it does NOT swap the nodes
    themselves.
*/
void swap_dpnodes(dpnode_t *n1, dpnode_t *n2) {
    footpath_segment_t *temp;
    temp = n1->fp;
    n1->fp = n2->fp;
    n2->fp = temp;
}

/*  Given a node in linked list, find the previous node and return it.
*/
dpnode_t *get_prev_dpnode(dpnode_t *start, dpnode_t *node) {
    dpnode_t *curr, *prev = NULL;
    curr = start;
    while (curr) {
        if (curr == node) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    return prev;
}

/*  Compare `footpath_id`. Order matters.
    Return values are:
    - [ < 0] `n` is smaller than `m`
    - [== 0] `n` is equal to `m`
    - [ > 0] `n` is larger than `m`
*/
int cmp_footpath_id(int n, int m) {
    return n - m;
}