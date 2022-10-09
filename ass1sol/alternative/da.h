#ifndef DA_H
#define DA_H
#include "data.h"

#define INITIAL_SIZE 1000

typedef struct {
    data_t** data;
    int used;
    int size;
} DA_t;

DA_t* make_DA();

void DAinsert(DA_t* dict, data_t* value);

void DAsearch(DA_t* dict, FILE* file_out, double value);

void DAfree(DA_t* dict, void (*freeData)(data_t* data));

#endif
