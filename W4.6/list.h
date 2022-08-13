/* Skeleton for W4.6, comp20003 workshop Week 4 */

/*-------------------------------------------------------------- 
..Project: qStud
  list.h :  
          = the interface of module linkedList of the project

  NOTES:
        - this module is polymorphic
        - the data component in a list node is of type void*
----------------------------------------------------------------*/
#ifndef _LIST_H_
#define _LIST_H_


// type definitions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct list list_t;


// generous functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// creates & returns an empty linked list
list_t *listCreate();

// free the list, with the help of function "freeData" for freeind data component
void listFree(list_t *list, void (*dataFree)(void *));

// returns 1 if the list is empty, 0 otherwise
int listIsEmpty(list_t *list); 

// returns the number of elements in list
int listCount(list_t *list);

// functions for insertion >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// inserts a new node with value "data" to the front of "list"
void listPrepend(list_t *list, void *data); 

// inserts a new node with value "data" to the end of "list" 
void listAppend(list_t *list, void *data); 


// functions for deletion >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// removes the first node of the list and returns the node's data
void *listDeleteHead(list_t *list); 

// removes the last node of the list and returns the node's data
void *listDeleteTail(list_t *list);

// applies function "f" to the data of all nodes
void listApplyIntFunc(list_t *list, void (*f)(void *));

// returns the (first-appeared) maximal data, using "compar" for comparing data
void *listMax(list_t *list, int (*compar) (const void *, const void *));

// performs linear search in "list", returns found data or NULL 
// here we assume that key is an int (a bad assumption, for sake of simplicity!)
void *listSearch(list_t *list, int key, int *comps, int (*dataGetKey)(void *));

#endif


/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 15/07/2022
   ================================================================== */

