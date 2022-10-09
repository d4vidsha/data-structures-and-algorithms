
#include "dict.h"
#define DEBUG 0

//#define DICT_STATICARRAY 1
//#include "staticarray.c"



dict_t* build_dict(int stage_num, FILE* file_in){
    dict_t* ret_val = (dict_t*) malloc(sizeof(dict_t));
    assert(ret_val);
    ret_val->dataset = (void*) make_LL();
    ret_val->insert = dictLLInsert;
    ret_val->search = dictLLSearch;
    ret_val->freeDict = dictLLFree;


    char c;
    while((c = fgetc(file_in)) != '\n');
    data_t* buffer;

    while((buffer = read_data_field(file_in))!=NULL){        
        ret_val->insert(ret_val, buffer);
        if(DEBUG)print_field(buffer,stdout);
    }


    
    if(stage_num == STAGE_2_VAL){
        //Store the orignal linked list for later use
        dict_t* ll_dict = ret_val;

        //Build a new dict from the linked list
        ret_val = (dict_t*) malloc (sizeof(dict_t));
        assert(ret_val);
        ret_val->dataset = (void*)make_DA();
        ret_val->insert = dictDAInsert;
        ret_val->search = dictDASearch;
        ret_val->freeDict = dictDAFree;
        data_t* buffer;
        while(((LL_t*) (ll_dict->dataset))->head != NULL){
            buffer = pop((LL_t*) (ll_dict->dataset));
            if(DEBUG) print_field(buffer, stdout);
            ret_val->insert(ret_val, buffer);
        }
    }

    return ret_val;
}

void search_dict(dict_t* dict, FILE* file_out, void* value){
    dict->search(dict->dataset, file_out, value);
}

void free_dict(dict_t* dict){
    dict->freeDict(dict->dataset);
    free(dict);
}

void dictLLInsert(dict_t* dict, data_t* value){
    LLinsert((LL_t*) dict->dataset, value);
}

void dictLLSearch(void* dataset, FILE* file_out, void* value){
    LLsearch((LL_t*) dataset, file_out, (char*) value);
}

void dictLLFree(void* dataset){
    LLfree((LL_t*) dataset, free_data);
}

void dictDAInsert(dict_t* dict, data_t* value){
    DAinsert((DA_t*)dict->dataset, value);
}

void dictDASearch(void* dataset, FILE* file_out, void* value){
    fprintf(file_out,"%s\n",(char*)value);
    fprintf(stdout,"%s --> ",(char*)value);
    DAsearch((DA_t*)dataset, file_out, strtod((char*)value,NULL));
}

void dictDAFree(void* dataset){
    DAfree((DA_t*)dataset,free_data);
}

/*
//Helper functions to typecast for static array insert/search
void insertfunc(void* dict, data_t* value){
    static_array_insert((staticarray_t*)dict,value);
}

data_t* searchfunc(void* dict, data_t value){
    return static_array_search((staticarray_t*)dict,value);
}

dict_t* make_dict(int dict_num){
    dict_t* ret_val = (dict_t*)malloc(sizeof(dict_t));
    ret_val->dataset = (staticarray_t*)malloc(sizeof(staticarray_t));
    ret_val->insert = insertfunc; //static_array_insert((staticarray_t*)ret_val, ...);//insertfunc;
    ret_val->search = searchfunc;
    return ret_val;
}

*/
