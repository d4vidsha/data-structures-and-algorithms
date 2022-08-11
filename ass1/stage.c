/* =============================================================================
   Project: dict1
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

void stage1(FILE *in, FILE *out) {
    // read footpath segments to a linked list
    list_t *list = create_empty_list();
    skip_header_line(in);
    build_list(in, list);

    // process queries on the fly
    char line[MAX_STR_LEN + NEWLINE_LEN + NULLBYTE_LEN];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;      // removes "\n" from line

        list_t *result_list = find_addresses(line, list);
        fprintf(out, "%s\n", line);
        print_footpath_segments(out, result_list);
        int list_length = list_len(result_list);
        if (list_length) {
            printf("%s --> %d\n", line, list_length);
        } else {
            printf("%s --> %s\n", line, NOTFOUND);
        }
        free_list(result_list);
    }

    // free everything
    free_list(list);
}

void stage2(FILE *in, FILE *out) {
    // read footpath segments to a linked list
    list_t *list = create_empty_list();
    skip_header_line(in);
    build_list(in, list);

    // sort list
    quicksort(list->head, list->foot);

    // process queries on the fly
    char line[MAX_STR_LEN + NEWLINE_LEN + NULLBYTE_LEN];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;      // removes "\n" from line
        char *ptr;
        double value = strtod(line, &ptr);
        list_t *result_list = linearsearch(value, list);
        fprintf(out, "%s\n", line);
        print_footpath_segments(out, result_list);
        printf("%s --> %lf\n", line, result_list->head->fp->grade1in);
        free_list(result_list);
    }

    // free everything
    free_list(list);
}

/* =============================================================================
   Written by David Sha.
   - Read line-by-line from stdin: https://stackoverflow.com/a/9206332/15444163
   - Remove newline from fgets: https://stackoverflow.com/a/28462221/15444163
============================================================================= */