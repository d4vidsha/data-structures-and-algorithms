/* =============================================================================
   Project: Assignment 2 (altered from Assignment 1)
   stage.c :
            = the stages of the project which processes queries on the fly
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stage.h"
#include "print.h"
#include "linkedlist.h"
#include "readcsv.h"
#include "data.h"
#include "quicksort.h"
#include "search.h"
#include "array.h"
#include "convert.h"

/*  Stage 1 of project.
*/
void stage1(FILE *out, list_t *list) {

    // process queries on the fly from `stdin`
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

        free_list(NOT_HOLLOW, result_list);
    }
    free_list(NOT_HOLLOW, list);
}

/*  Stage 2 of project.
*/
void stage2(FILE *out, list_t *list) {

    // sort linked list from lowest to highest by the given column index
    // note that there is a better function to sort data
    // see `quicksort_array()` for more details.
    quicksort(list, COLUMN_INDEX_GRADE1IN);

    // convert linked list to array and remove linked list
    array_t *array = convert_to_array(NOT_HOLLOW, list);
    free_list(NOT_HOLLOW, list);

    // process queries on the fly from `stdin`
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
        
        free_array(NOT_HOLLOW, results);
    }
    free_array(NOT_HOLLOW, array);
}

/*  Stage 3 of project.
*/
void stage3(FILE *out, qtnode_t *tree) {

    // process queries on the fly from `stdin`
    char line[MAX_STR_LEN + NEWLINE_LEN + NULLBYTE_LEN];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;      // removes "\n" from line

        // parse string to double
        double x, y;
        char *ptr = line;
        x = strtod(ptr, &ptr);
        y = strtod(ptr, &ptr);
        point2D_t *point = create_point(x, y);

        // search for the point returning a pointer to the results
        // directly on the quadtree
        printf("%s -->", line);
        dpll_t *results = search_quadtree(tree, point);

        // print the results to `out` file
        fprintf(out, "%s\n", line);
        if (results) {
            // sort results
            array_t *resarr = convert_dpll_to_array(HOLLOW, results);
            quicksort_array(COLUMN_INDEX_FPID, resarr, 0, resarr->n - 1);
            check_array_sorted(COLUMN_INDEX_FPID, resarr);
            
            // print results
            print_array(out, resarr);
            free_array(HOLLOW, resarr);
        }
        free_point(point);
    }
}

/*  Stage 4 of project.
*/
void stage4(FILE *out, qtnode_t *tree) {

    // process queries on the fly from `stdin`
    char line[MAX_STR_LEN + NEWLINE_LEN + NULLBYTE_LEN];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;      // removes "\n" from line

        // parse string to double
        long double x, y;
        point2D_t *bl, *tr;
        char *ptr = line;
        x = strtold(ptr, &ptr);
        y = strtold(ptr, &ptr);
        bl = create_point(x, y);
        x = strtold(ptr, &ptr);
        y = strtold(ptr, &ptr);
        tr = create_point(x, y);
        rectangle2D_t *range = create_rectangle(bl, tr);
        free_point(bl);
        free_point(tr);

        // range search for all datapoints within range with `results`
        // being a hollow `dpll` i.e. list only has pointers to data from
        // the quadtree
        printf("%s -->", line);
        dpll_t *results = create_empty_dpll();
        range_search_quadtree(results, tree, range);
        free_rectangle(range);
        printf("\n");

        // initiate printing the results to `out` file
        fprintf(out, "%s\n", line);

        // sort results
        array_t *resarr = convert_dpll_to_array(HOLLOW, results);
        free_dpll(HOLLOW, results);
        quicksort_array(COLUMN_INDEX_FPID, resarr, 0, resarr->n - 1);
        check_array_sorted(COLUMN_INDEX_FPID, resarr);
        
        // deduplicate results
        list_t *reslist = convert_array_to_list(HOLLOW, resarr);
        free_array(HOLLOW, resarr);

        // finally print results
        print_distinct_list(out, COLUMN_INDEX_FPID, reslist);
        free_list(HOLLOW, reslist);
    }
}

/* =============================================================================
   Written by David Sha.
   - Read line-by-line from stdin: https://stackoverflow.com/a/9206332/15444163
   - Remove newline from fgets: https://stackoverflow.com/a/28462221/15444163
============================================================================= */