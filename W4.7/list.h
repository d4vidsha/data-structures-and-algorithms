/* Skeleton for W4.7, comp20003 workshop Week 4 */

/*-------------------------------------------------------------- 
..Project: postfix
  list.[c,h] :  module lineked list of the project
----------------------------------------------------------------*/


#ifndef _LIST_H_
#define _LIST_H_


// type definitions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct list list_t;

// generous functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// creates & returns an empty linked list
list_t *listCreate();

// free the list, with the help of function "freeData" for freeind data component
void listFree(list_t *list);

// returns 1 if the list is empty, 0 otherwise
int listIsEmpty(list_t *list); 

// returns the number of elements in list
int listCount(list_t *list);

// inserts a new node with value "data" to the front of "list"
void listPrepend(list_t *list, int data); 

// removes the first node of the list and returns the node's data
int listDeleteHead(list_t *list); 

#endif


/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 15/07/2022
   ================================================================== */

