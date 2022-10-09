#ifndef DICT_H
#define DICT_H
#include "data.h"
#include "ll.h"
#include "da.h"
#include <stdlib.h>
#include <stdio.h>

#define STAGE_2_VAL 2

typedef struct dictionary dict_t;

struct dictionary{
    void* dataset;
    void (*insert)(dict_t* dict, data_t* value);
    void (*search)(void* dataset, FILE* file_out, void* value);
    void (*freeDict)(void* dict);
};
dict_t* build_dict(int stage_num, FILE* file_in);
void search_dict(dict_t* dict, FILE* file_out, void* value);
void free_dict(dict_t* dict);
void dictLLInsert(dict_t* dict, data_t* value);
void dictLLSearch(void* dataset, FILE* file_out, void* value);
void dictLLFree(void* dataset);
void dictDAInsert(dict_t* dict, data_t* value);
void dictDASearch(void* dataset, FILE* file_out, void* value);
void dictDAFree(void* dataset);

#endif