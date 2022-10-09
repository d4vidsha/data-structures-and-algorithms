/*
    A dictionary which allows the lookup of a list of addresses at the command
    line.

    Compile with
        make dict3
    
    Run with
        ./dict3 3 <input dataset> <output file> <region start_lat> \
            <region start_lon> <region end_lat> <region end_lon> \
            < <keys file>
    Where
        <input dataset> is the filename of the input csv.
        <output file> is the filename of the output text file.
        <keys file> is a list of keys separated by newlines.
        <region start_lon> is the start longitude for the bounding rectangle
        <region start_lat> is the start latitude for the bounding rectangle
        <region end_lon> is the end longitude for the bounding rectangle
        <region end_lat> is the end latitude for the bounding rectangle
    
    Written by Grady Fitzpatrick for COMP20003 as a sample solution
    for Assignment 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "read.h"
#include "dictionary.h"

#define MINARGS 8
#define EXPECTED_STAGE "3"
#define STAGE (QTLOOKUP)
#define PRIMARY_KEY_FIELD 0
#define INDEX_FIELD 6
#define INDEX_FIELD_LON_START 16
#define INDEX_FIELD_LAT_START 15
#define INDEX_FIELD_LON_END   18
#define INDEX_FIELD_LAT_END   17

int main(int argc, char **argv){
    if(argc < MINARGS){
        fprintf(stderr, "Insufficient arguments, run in form:\n"
            "\t./dict3 3 <input dataset> <output file> \\\n"
            "\t\t<region start_lat> <region start_lon> \\\n"
            "\t\t<region end_lat> <region end_lon> \\\n"
            "\t\t< <keys file>\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(EXPECTED_STAGE, argv[1]) != 0){
        fprintf(stderr, "Expected stage was %s, received %s\n", EXPECTED_STAGE, argv[1]);
        exit(EXIT_FAILURE);
    }

    char *inputCSVName = argv[2];
    char *outputFileName = argv[3];
    long double startLon = strtold(argv[4], NULL);
    long double startLat = strtold(argv[5], NULL);
    long double endLon = strtold(argv[6], NULL);
    long double endLat = strtold(argv[7], NULL);

    FILE *csvFile = fopen(inputCSVName, "r");
    assert(csvFile);
    FILE *outputFile = fopen(outputFileName, "w");
    assert(outputFile);
    
    int n;
    struct csvRecord **dataset = readCSV(csvFile, &n);

    struct dictionary *dict = newDict();

    long double pointsStart[] = { startLon, startLat };
    long double pointsEnd[] = { endLon, endLat };
    unsigned int dim = sizeof(pointsStart) / sizeof(pointsStart[0]);
    unsigned int fieldIndices[2][dim];
    fieldIndices[0][0] = INDEX_FIELD_LON_START;
    fieldIndices[0][1] = INDEX_FIELD_LAT_START;
    fieldIndices[1][0] = INDEX_FIELD_LON_END;
    fieldIndices[1][1] = INDEX_FIELD_LAT_END;
    /* Store explicit pointers so we can access values inside C arrays. */
    unsigned int *(fieldIndicesPointers[]) = { &(fieldIndices[0][0]), 
        &(fieldIndices[1][0]) };
    unsigned int fieldIndexCount = sizeof(fieldIndices)/(dim * 
        sizeof(fieldIndices[0][0]));

    reconfigureSearchBounds(dict, pointsStart, pointsEnd, dim, 
        fieldIndicesPointers, fieldIndexCount);

    for(int i = 0; i < n; i++){
        insertRecord(dict, dataset[i]);
    }
    freeCSV(dataset, n);

    char *query = NULL;
    while((query = getQuery(stdin))){
        struct queryResult *r = searchQT(dict, query, PRIMARY_KEY_FIELD);
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
