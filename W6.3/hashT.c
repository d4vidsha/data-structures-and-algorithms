#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hashT.h"

/* A sentinal value signifying no value is in the space. */
#define SENTINEL (-1)

struct hashTable {
    int size;
    int used;
    int *data;
    int (*hash)(int);
    void (*insert)(struct hashTable *, int, int);
    void (*print)(int);
};

void insertLP(struct hashTable *table, int key, int value){
    /* Write this. NOTE: if you have already written insertDH,
        this is one line of code. */
        
}

void insertDH5(struct hashTable *table, int key, int value){
    /* Write code to calculate the interval from the value and 
        then call insertDH with this interval. */
    int interval = 5;
    insertDH(table, key, value, interval);
}

void insertDH(struct hashTable *table, int key, int value, int hash2key){
    /* Write this. */
    
    
    
    
}

struct hashTable *create(int tableSize, int (*hash)(int), 
    void (*insert)(struct hashTable *, int, int), void (*print)(int)){
    int i;
    struct hashTable *returnTable = (struct hashTable *) malloc(sizeof(struct hashTable));
    assert(returnTable);
    
    returnTable->size = tableSize;
    returnTable->used = 0;
    returnTable->hash = hash;
    returnTable->insert = insert;
    returnTable->print = print;
    returnTable->data = (int *) malloc(sizeof(int)*tableSize);
    assert(returnTable->data);
    
    /* Set all elements to NULL, so we know which elements
        are used. */
    for(i = 0; i < tableSize; i++){
        (returnTable->data)[i] = SENTINEL;
    }
    
    return returnTable;
}

void insert(struct hashTable *table, int value){
    int key;
    key = table->hash(value);
    table->insert(table, key, value);
}

void printTable(struct hashTable *table){
    int i;
    printf("|");
    for(i = 0; i < table->size; i++){
        if(table->data[i] != SENTINEL){
            table->print(table->data[i]);
        } else {
            printf(" ");
        }
        printf("|");
    }
    printf("\n");
}

void freeTable(struct hashTable *table){
    free(table->data);
    free(table);
}
