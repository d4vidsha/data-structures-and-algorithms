/* Skeleton for W4.7, comp20003 workshop Week 4 */
/*-------------------------------------------------------------- 
..Project: postfix
  list.[c,h] :  module lineked list of the project
----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

void error(char *name) {
	fprintf(stderr, "Function %s not yet implemented.\n", name);
	exit(EXIT_FAILURE);
}

// data definitions, internal within list.checks >>>>>>>>>>>>>>>>>>>>>>>>>>
// a list node 
typedef struct node node_t;
struct node {
	int data;                // data is just an int
	node_t *next;            // points to the next node in the list
};

// a linked list is defined as a couple of pointers
struct list {
	node_t *head;  // points to the first node of the list
	node_t *tail;  // points to the last node of the list 
	size_t n;               // number of element in the list
};


// generous functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// creates & returns an empty linked list
list_t *listCreate() {
	list_t *list = malloc(sizeof(*list));
	assert(list);
	list->head = list->tail = NULL;
	list->n = 0;
	return list;
}

// free the list
void listFree(list_t *list){
	assert(list != NULL);
	node_t *curr = list->head; // curr points to the first node
	while (curr) {             // while curr not reaching the end of list
		node_t *tmp = curr;
		curr = curr->next;     // advance curr to the next next node 
		free(tmp);             //    freeing the space used by data
	}
	free(list);                // free the list itself
} 

// returns 1 if the list is empty, 0 otherwise
int listIsEmpty(list_t *list) {
	assert(list);
	return list->head == NULL;
}

// returns the number of elements in list
int listCount(list_t *list){
	assert(list);
	return list->n;
}

// functions for insertion >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// inserts a new node with value "data" to the front of "list"
void listPrepend(list_t *list, int data) {
	assert(list);

	// creates a new node and set data 
	node_t *new = malloc(sizeof(*new));
	assert(new);
	new->data = data;
	
	// links the new node to the list
	new->next = list->head;     // connects "new" to the head node
	list->head = new;           // repairs the pointer "head"

	// checks special condition of inserting the the initially empty list
	if (list->tail == NULL) {      // original list is empty
		list->tail = new;   // so "new" is also the tail node
	}

	// updates the number of elements in the list
	(list->n)++;
}

 

// removes the first node of the list and returns the node's data
int listDeleteHead(list_t *list) {
	assert(list && list->head);
	node_t *tmp = list->head;      // the first, being-removed node 
	int data = tmp->data;          // the returned data

	// remove the node from the list
	list->head = list->head->next; // links "head" to the second node
	if (list->head == NULL) {       // if the list becomes empty 
		list->tail = NULL;     //   then the "tail" must also be NULL
	}
	free(tmp);                    // free the removed node

	// updates the number of elements in the list
	(list->n)--;

	return data;
} 


/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 15/07/2022
   ================================================================== */

