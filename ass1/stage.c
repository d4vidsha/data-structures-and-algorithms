/* =============================================================================
   Project: Assignment 1
   stage.c :
            = the stages of the project
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stage.h"
#include "linkedlist.h"
#include "readcsv.h"
#include "data.h"
#include "quicksort.h"
#include "search.h"
#include "array.h"

/*  Stage 1 of project.
*/
void stage1(FILE *in, FILE *out) {

    // read footpath segments to a linked list
    list_t *list = create_empty_list();
    skip_header_line(in);
    build_list(in, list);

    // process queries on the fly
    char line[MAX_STR_LEN + NEWLINE_LEN + NULLBYTE_LEN];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;      // removes "\n" from line

        // find addresses
        list_t *result_list = find_addresses(line, list);

        // print to `out` file
        fprintf(out, "%s\n", line);
        print_list(out, result_list);
        
        // print to `stdout`
        int list_length = list_len(result_list);
        if (list_length) {
            printf("%s --> %d\n", line, list_length);
        } else {
            printf("%s --> %s\n", line, NOTFOUND);
        }

        free_list(result_list);
    }
    free_list(list);
}

/*  Stage 2 of project.
*/
void stage2(FILE *in, FILE *out) {

    // read footpath segments to a linked list
    list_t *list = create_empty_list();
    skip_header_line(in);
    build_list(in, list);

    // sort linked list from lowest to highest by the given column index
    quicksort(list, COLUMN_INDEX_GRADE1IN);

    // convert linked list to array and remove linked list
    array_t *array = convert_to_array(list);
    free_list(list);

    // process queries on the fly
    char line[MAX_STR_LEN + NEWLINE_LEN + NULLBYTE_LEN];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;      // removes "\n" from line

        // parse string to double
        char *ptr;
        double value = strtod(line, &ptr);

        // search through linked list for closest match
        array_t *results = binarysearch(value, array);
        
        // print to `out` file
        fprintf(out, "%s\n", line);
        print_array(out, results);

        // print to `stdout`
        printf("%s --> %.1lf\n", line, results->A[0]->grade1in);
        
        free_array(results);
    }
    free_array(array);
}

/* =============================================================================
   Written by David Sha.
   - Read line-by-line from stdin: https://stackoverflow.com/a/9206332/15444163
   - Remove newline from fgets: https://stackoverflow.com/a/28462221/15444163
============================================================================= */