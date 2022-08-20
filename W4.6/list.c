/* Skeleton for W4.6, comp20003 workshop Week 4 */

/*-------------------------------------------------------------- 
..Project: qStud
  list.h :  
          = the implementation of module linkedList of the project

  NOTES:
        - this module is polymorphic
        - the data component in a list node is of type void*
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
	void *data;              // points to the data element of the node
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
/* free all memory used by a list, including used by data component
    requires argument dataFree which is a function
    the parameter can be declared as function pointer, as broken down belows:
           (*dataFree)           : dataSize is a pointer to
           (*dataFree)(void *)   :  a function that has "void *" as argument
      void (*dataFree)(void *)   :  and that returns void
    (the above break-down is application of the right-left rule, 
      see https://cseweb.ucsd.edu/~gbournou/CSE131/rt_lt.rule.html)
*/
void listFree(list_t *list, void (*dataFree)(void *)){
	assert(list != NULL);
	node_t *curr = list->head; // curr points to the first node
	while (curr) {             // while curr not reaching the end of list
		node_t *tmp = curr;
		curr = curr->next;     // advance curr to the next next node 
		dataFree(tmp->data);       // frees the previous node including
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
void listPrepend(list_t *list, void *data) {
	assert(list);

	// creates a new node and set data 
	node_t *new = malloc(sizeof(*new));
	assert(new);
	new->data = data;
	
	// links the new node to the list
	new->next = list->head;     // connects "new" to the head node
	list->head = new;           // repairs the pointer "head"

	// checks special condition of inserting the the initially empty list
	if (list->tail == NULL){       // original list is empty
		list->tail = new;   // so "new" is also the tail node
	}
	// updates the number of elements in the list
	(list->n)++;
}

// inserts a new node with value "data" to the end of "list" 
void listAppend(list_t *list, void *data) {
	assert(list);

	// creates a new node and set data 
	node_t *new = malloc(sizeof(*new));
	assert(new);
	new->data = data;
	// FILL IN
	// error("listAppend");
	new->next = NULL;
	if (list->tail == NULL) {
		list->head = list->tail = new;
		list->n = 1;
	} else {
		list->tail->next = new;
		list->tail = new;
		(list->n)++;
	}
}


// functions for deletion >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// removes the first node of the list and returns the node's data
void *listDeleteHead(list_t *list) {
	assert(list && list->head);
	node_t *tmp = list->head;      // the first, being-removed node 
	void *data = tmp->data;        // the returned data

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

// removes the last node of the list and returns the node's data
void *listDeleteTail(list_t *list){
	assert(list && list->head);
	node_t *tmp = list->tail;      // the last, being-removed node 
	void *data = tmp->data;        // the returned data

	// remove the node from the list
	if (list->n == 1) {                     // if the original list has just one node 
		list->head = list->tail = NULL; //   it becomes empty
	} else {                      // here the list has >1 nodes 
		// Step 1: finds "prev" = second last node, which points to "tail"
		node_t *prev = list->head;
		while (prev->next != list->tail) {
			prev = prev->next;
		}

		// Step 2: makes prev become the last node
		prev->next = NULL;       // prev does not have follower anymore
		list->tail = prev;       // and tail now point to the new last node
	}

	free(tmp);                      // free the removed node

	// updates the number of elements in the list
	(list->n)--;

	return data;
}


// functions for processing over the whole list >>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// applies function "f" to the data of all nodes
//  note that "f" could return "void"
//  but it doesn't hurt, and is more useful, with retruing "int"
void listApplyIntFunc(list_t *list, void (*f)(void *)) {
	assert(list);
	for (node_t *p = list->head; p; p = p->next) {
		f(p->data);
	}
}

// returns the (first-appeared) maximal data, using "compar" for comparing data
void *listMax(list_t *list, int (*compar) (const void *, const void *)){
	assert(list);
	if (list->head == NULL) return NULL;

	void *max = list->head;
	for (node_t *p = list->head->next; p; p = p->next) {
		if (compar(p->data, max) > 0) {
			max = p->data;
		}
	}
	return max;
}

// performs linear search in "list", returns found data or NULL 
// here we assume that key is an int (a bad assumption for sake of simplicity!)
void *listSearch(list_t *list, int key, int *comps, int (*dataGetKey)(void *)) {
	void *soln = NULL;
	/* FILL IN */
	// error("listSearch");
	node_t *curr = list->head;
	*comps = 0;
	while (curr) {
		(*comps)++;
		if (key == dataGetKey(curr->data)) {
			soln = curr;
			break;
		}
		curr = curr->next;
	}
	return soln;
}



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 15/07/2022
   ================================================================== */

