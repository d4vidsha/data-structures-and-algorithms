#ifndef _DATA_H_
#define _DATA_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define MAX_STR_LEN 128
#define MAX_BUF_LEN 512

//When reading string, can delimit string with " " to allow for commas

typedef struct{
    int footpath_id;
    char* address;
    char* clue_sa;
    char* asset_type;
    double deltaz;
    double distance;
    double grade1in;
    int mcc_id;
    int mccid_int;
    double rlmax;
    double rlmin;
    char* segside;
    int statusid;
    int streetid;
    int street_group;
    double start_lat;
    double start_lon;
    double end_lat;
    double end_lon;
    
    //Used for DEBUG
    int a;
} data_t;

data_t* read_data_field(FILE* file_in);
char* read_string(FILE* file_in);
void print_data(FILE* file_out);
void print_field(data_t* value, FILE* file_out);
int is_address_match(char* addr1, char* addr2);
data_t* best_grade1in(data_t* data1, data_t* data2, double value);
void free_data(data_t* data);


#endif
