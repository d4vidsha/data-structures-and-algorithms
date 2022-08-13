/* Skeleton for W4.5, comp20003 workshop Week 4 */

// aka. list4.c 22s1 week4

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// define struct for a node
struct node {
    int data;
    struct node *next;
};

int main(int argc, char *argv[]) {
    struct node *head;
    head = malloc(sizeof(*head));
    assert(head);
    head->data = 5;

    // FILL IN THE REST FOR NODES 10, 20, 1
    // int arr[] = {10, 20, 1};
    // int n = 3;
    // for (int i = 0; i < n; i++) {
    struct node *node;
    node = (struct node *)malloc(sizeof(*head));
    assert(node);
    node->data = 10;
    head->next = node;
    

    return 0;
}


/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 15/07/2022
   ================================================================== */

