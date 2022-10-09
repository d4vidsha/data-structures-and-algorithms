#include "da.h"
#define DEBUG 0

DA_t* make_DA(){
    DA_t* ret_val = (DA_t *) malloc(sizeof(DA_t));
    assert(ret_val);
    ret_val->used = 0;
    ret_val->size = INITIAL_SIZE;
    ret_val->data = (data_t **) malloc(ret_val->size * sizeof(data_t *));
    assert(ret_val->data);
    return ret_val;
}

void DAinsert(DA_t* dict, data_t* value){
    if(DEBUG) printf("Inserting %lf into DA\n", value->grade1in);
    assert(dict->used < dict->size);
    dict->data[dict->used++] = value;
}

void DAsearch(DA_t* dict, FILE* file_out, double value){
    if(DEBUG) printf("Searching DA for %f\n", value);
    data_t* best = dict->data[0];
    for(int i = 1; i < dict->used;i++){
        best=best_grade1in(dict->data[i], best, value);
    }
    print_field(best, file_out);
    fprintf(stdout, "%.1lf\n", best->grade1in);
}

void DAfree(DA_t* dict, void (*freeData)(data_t* data)){
    for(int i = 0; i < dict->used; i++){
        freeData(dict->data[i]);
    }
    free(dict);
}


