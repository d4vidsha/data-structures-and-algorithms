/* =============================================================================
   Project: Assignment 2 (altered from Assignment 1)
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
        
        free_array(results);
    }
    free_array(array);
}

void stage3(FILE *in, FILE *out, rectangle2D_t *region) {
    // make copy of `region` for use later
    rectangle2D_t *r = rectangle_cpy(region);

    // read footpath segments to a linked list
    list_t *list = create_empty_list();
    skip_header_line(in);
    build_list(in, list);

    // construct quadtree from linked list
    qtnode_t *tree = create_quadtree(list, r);
    
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

        // search for the point
        printf("%s -->", line);
        dpll_t *results = search_quadtree(tree, point);

        // print the results to `out` file
        fprintf(out, "%s\n", line);
        if (results) {
            // quicksort_dpll(results); // need to implement sorting algorithm
            print_dpll(out, results);
        }

        free_point(point);
    }

    // free everything
    free_quadtree(tree);
    free_list(list);
}

void stage4(FILE *in, FILE *out, rectangle2D_t *region) {
    // make copy of `region` for use later
    rectangle2D_t *r = rectangle_cpy(region);

    // read footpath segments to a linked list
    list_t *list = create_empty_list();
    skip_header_line(in);
    build_list(in, list);

    // construct quadtree from linked list copying over all data from
    // linked list
    qtnode_t *tree = create_quadtree(list, r);

    // free list containing all its data
    // Note that quadtree is still usable as the data was completely copied
    // from linked list. We call a copy "hollow" when only the pointers to
    // the data are copied. In this case, `create_quadtree()` is not hollow,
    // and the data copied from linked list are of type `footpath_segment_t`
    // which was manipulated to generate `datapoint_t` datatype for the 
    // quadtree.
    free_list(list);

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

        // range search for all datapoints within range with `results`
        // being a hollow dpll i.e. list only has pointers to data from
        // the quadtree
        printf("%s -->", line);
        dpll_t *results = create_empty_dpll();
        range_search_quadtree(results, tree, range);
        printf("\n");

        // print the results to `out` file
        fprintf(out, "%s\n", line);
        if (results) {
            // array_t *resarr = convert_dpll_to_array(results);
            // quicksort_array(COLUMN_INDEX_FPID, resarr, 0, resarr->n - 1);
            // list_t *reslist = convert_array_to_list(resarr);
            // free_hollow_array(resarr);
            // // dedup_list(results);
            // print_list(out, reslist);
            // free_hollow_list(reslist);
        }

        free_dpll(results, HOLLOW);
        free_point(bl);
        free_point(tr);
        free_rectangle(range);
    }

    // free everything else
    free_quadtree(tree);
}

/* =============================================================================
   Written by David Sha.
   - Read line-by-line from stdin: https://stackoverflow.com/a/9206332/15444163
   - Remove newline from fgets: https://stackoverflow.com/a/28462221/15444163
============================================================================= */