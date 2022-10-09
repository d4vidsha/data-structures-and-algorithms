#ifndef LL_H
#define LL_H
#include "data.h"

typedef struct node node_t;

struct node{
	data_t* data;
	node_t* next;
};

typedef struct{
    node_t* head;
    node_t* tail;
}LL_t;


LL_t* make_LL();

void LLinsert(LL_t* list, data_t* value);

data_t* pop(LL_t* list);

void LLsearch(LL_t* list, FILE* file_out, char* value);

void LLfree(LL_t* list, void (*freeData)(data_t* data));

#endif