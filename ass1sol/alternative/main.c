#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "dict.h"

#define DEBUG 0
#define STAGE_1 "1"
#define STAGE_2 "2"
        
#define BUFFER_LENGTH 1000

int main(int argc, char* argv[]){
    if(argc != 4){
        printf("Incorrect input, need 4 arguments:\nstage,data,outfile\n");
        return 1;
    }
    //FILE* file_in = fopen("home/dataset_1.csv","r");
    FILE* file_in = fopen(argv[2], "r");
    FILE* file_out = fopen(argv[3], "w");
    assert(file_in && file_out);

    //read data from file_in
    //store in LL
    //if Stage 2 ... Construct sorted array of pointers to each LL node based on index 6 (grade1in)
        
    int stage_num = atoi(argv[1]);
    dict_t* dict = build_dict(stage_num, file_in);
    fclose(file_in);

    //Check stage for output
    if((strcmp(argv[1], STAGE_1) == 0) || (strcmp(argv[1], STAGE_2) == 0)){
        if(DEBUG){
            printf("Running stage 1\n\n");
        }
        //accept "addresses" from stdin (each seperated by \n) 
        //search for "addresses" in LL and print record_data and records found (or print NOTFOUND) to file_out
        char buffer[BUFFER_LENGTH + 1];
        char c;
        int i;
        while(1){
            for(i = 0; (c = getchar()) != EOF && c != '\n'; buffer[i++] = c);
            if(c == EOF){break;}
            buffer[i] = '\0';
            if(DEBUG)printf("Searching for : %s\n", buffer);

            search_dict(dict, file_out, (void*) buffer);
        }
    }
    else if(strcmp(argv[1], STAGE_2) == 0){ 
        if(DEBUG){
            printf("Running stage 2\n\n");
        }
        //accept double from stdin
        //search for index to closest value  (abs difference) (pick any if equal) and print grade1in value
        double buffer;
        while(scanf("%lf\n", &buffer) == 1){
            search_dict(dict, file_out, (void*) &buffer);
        }

    }  
    else{
        printf("Incorrect input, need 4 arguments:\nstage,data,outfile\n");
        return 1;
    }
    free_dict(dict);
    fclose(file_out);

    /*Some sample code to test the dictionary
    if(DEBUG){
        dict_t* dict1 = make_dict(DICT_STATICARRAY);
        data_t a = {3};
        data_t b = {7};
        dict1->insert(dict1,&a);
        dict1->insert(dict1,&a);
        dict1->insert(dict1,&b);
        data_t* search1 = (data_t*)(dict1->search(dict1,a));
        data_t* search2 = (data_t*)(dict1->search(dict1,b));
        //data_t search3 = dict1->search(dict1,3);
        printf("%d\n%d\n%d\n",search1->key,search2->key,search1->key);
    }*/

    return 0;
}
