#include "ll.h"


LL_t* make_LL(){
    LL_t* ret_val = (LL_t*) malloc(sizeof(LL_t));\
    assert(ret_val);
    ret_val->head = NULL;
    ret_val->tail = NULL;
    return ret_val;
}

void LLinsert(LL_t* list, data_t* value){
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    assert(new_node);
    new_node->data = value;
    new_node->next = NULL;
    if(list->head == NULL){
        list->head = list->tail = new_node;
    }
    else{
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

data_t* pop(LL_t* list){
    assert(list->head != NULL);
    data_t* ret_val = list->head->data;
    node_t* oldhead = list->head;
    list->head = list->head->next;
    free(oldhead);
    return ret_val;
}

void LLsearch(LL_t* list, FILE* file_out, char* value){
    assert(list->head);
    node_t* curr = list->head;

    fprintf(file_out,"%s\n",value);
    int num_matches = 0;
    while(curr){
        if(curr->data->address == NULL){
            curr = curr->next;
            continue;
        }
        if(is_address_match(curr->data->address, value)){
            print_field(curr->data, file_out);
            num_matches++;
        }
        curr = curr->next;
    }
    if(num_matches){
        fprintf(stdout, "%s --> %d\n", value, num_matches);
    }
    else{
        fprintf(stdout, "%s --> NOTFOUND\n",value);
    }
}

void LLfree(LL_t* list, void (*freeData)(data_t* data)){
    assert(list->head);
    node_t* curr = list->head;
    node_t* next;
    while(curr){
        next = curr->next;
        freeData(curr->data);
        free(curr);
        curr = next;
    }
    free(list);
}

