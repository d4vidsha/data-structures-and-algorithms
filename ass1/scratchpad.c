#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct node node_t;
struct node {
    int *fp;
    node_t *next;
};

typedef struct list list_t;
struct list {
    node_t *head;
    node_t *foot;
};

list_t *create_empty_list(void) {
    list_t *list;
    list = (list_t *)malloc(sizeof(*list));
    assert(list);
    list->head = list->foot = NULL;
    return list;
}

list_t *append(list_t *list, int *fp) {
    node_t *new;
    assert(list);
    new = (node_t *)malloc(sizeof(*new));
    assert(new);
    new->fp = fp;
    new->next = NULL;
    if (list->foot == NULL) {
        /* this is the first insert into list */
        list->head = list->foot = new;
    } else {
        list->foot->next = new;
        list->foot = new;
    }
    return list;
}

void swap(node_t *n1, node_t *n2) {
    printf("swapping %d with %d\n", *(n1->fp), *(n2->fp));
    int *temp;
    // temp = (int *) malloc(sizeof(*temp));
    // assert(temp);
    // memcpy(temp, n1->fp, sizeof(*temp));
    temp = n1->fp;
    n1->fp = n2->fp;
    n2->fp = temp;
    // free(temp);
}

node_t *partition(node_t *low, node_t *high) {

    node_t *pivot = high;
    node_t *i = low;
    node_t *j = low;

    printf("%d %d %d\n", *(pivot->fp), *(i->fp), *(j->fp));
    // j = j->next;
    // printf("%d %d %d\n", *(pivot->fp), *(i->fp), *(j->fp));
    // swap(i, j);

    while (j != NULL && j != high) {
        if (*(j->fp) < *(pivot->fp)) {
            assert(i != NULL && j != NULL);
            swap(i, j);
            i = i->next;
        }
        j = j->next;
    }
    assert(i != NULL);
    printf("Final swap: ");
    swap(i, pivot);

    return pivot;
}

/* Provided a file output `f`, print the list in the specified format.
*/
void print_list(list_t *list) {
    assert(list);
    node_t *curr;
    curr = list->head;
    while (curr) {
        fprintf(stdout, "%d", *(curr->fp));
        fprintf(stdout, "\n");
        curr = curr->next;
    }
}

int main(int argc, char *argv[]) {

    // int footpath_id;
    // char address[MAX_STR_LEN + NULLBYTE];
    // char clue_sa[MAX_STR_LEN + NULLBYTE];
    // char asset_type[MAX_STR_LEN + NULLBYTE];
    // double deltaz;
    // double distance;
    // double grade1in;
    // int mcc_id;
    // int mccid_int;
    // double rlmax;
    // double rlmin;
    // char segside[MAX_STR_LEN + NULLBYTE];
    // int statusid;
    // int streetid;
    // int street_group;
    // double start_lat;
    // double start_lon;
    // double end_lat;
    // double end_lon;

    // if (read_fields == NUM_FIELDS) {
        // fp->footpath_id = footpath_id;
        // strcpy(fp->address, address);
        // strcpy(fp->clue_sa, clue_sa);
        // strcpy(fp->asset_type, asset_type);
        // fp->deltaz = deltaz;
        // fp->distance = distance;
        // fp->grade1in = grade1in;
        // fp->mcc_id = mcc_id;
        // fp->mccid_int = mccid_int;
        // fp->rlmax = rlmax;
        // fp->rlmin = rlmin;
        // strcpy(fp->segside, segside);
        // fp->statusid = statusid;
        // fp->streetid = streetid;
        // fp->street_group = street_group;
        // fp->start_lat = start_lat;
        // fp->start_lon = start_lon;
        // fp->end_lat = end_lat;
        // fp->end_lon = end_lon;
    // } else {
    //     fprintf(stderr, "ERROR: failed to scan all required fields\n");
    // }
    // printf("%d %d\n", EXIT_SUCCESS, EXIT_FAILURE);

    list_t *list = create_empty_list();
    int fp1, fp2, fp3;
    fp1 = 6;
    list = append(list, &fp1);
    fp2 = 2;
    list = append(list, &fp2);
    fp3 = 4;
    list = append(list, &fp3);
    print_list(list);
    printf("\n");
    partition(list->head, list->foot);
    print_list(list);
    
    return EXIT_SUCCESS;
}

