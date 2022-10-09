/*
    A dictionary which allows the lookup of a list of addresses at the command
    line.

    Compile with
        make dict2
    
    Run with
        ./dict2 2 <input dataset> <output file> < <keys file>
    Where
        <input dataset> is the filename of the input csv.
        <output file> is the filename of the output text file.
        <keys file> is a list of keys separated by newlines.
    
    Written by Grady Fitzpatrick for COMP20003 as a sample solution
    for Assignment 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "read.h"
#include "dictionary.h"

#define MINARGS 4
#define EXPECTED_STAGE "2"
#define STAGE (PROXIMITYSTAGE)
#define INDEX_FIELD 6

int main(int argc, char **argv){
    if(argc < MINARGS){
        fprintf(stderr, "Insufficient arguments, run in form:\n"
                        "\t./dict2 2 <input dataset> <output file> < <keys file>\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(EXPECTED_STAGE, argv[1]) != 0){
        fprintf(stderr, "Expected stage was %s, received %s\n", EXPECTED_STAGE, argv[1]);
        exit(EXIT_FAILURE);
    }

    char *inputCSVName = argv[2];
    char *outputFileName = argv[3];

    FILE *csvFile = fopen(inputCSVName, "r");
    assert(csvFile);
    FILE *outputFile = fopen(outputFileName, "w");
    assert(outputFile);
    
    int n;
    struct csvRecord **dataset = readCSV(csvFile, &n);

    struct dictionary *dict = newDict();

    for(int i = 0; i < n; i++){
        insertRecord(dict, dataset[i]);
    }
    freeCSV(dataset, n);

    char *query = NULL;
    while((query = getQuery(stdin))){
        struct queryResult *r = searchClosestDouble(dict, query, INDEX_FIELD);
        printQueryResult(r, stdout, outputFile, STAGE);
        freeQueryResult(r);
        free(query);
    }

    freeDict(dict);
    dict = NULL;

    fclose(csvFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}
