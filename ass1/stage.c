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
    fprintf(out, "BEFORE\n");
    print_footpath_segments(out, list);
    quicksort(list->head, list->foot);
    fprintf(out, "\nAFTER\n");
    print_footpath_segments(out, list);
    print_grade1in(out, list);

    // process queries on the fly

    // free everything
    free_list(list);
}

/* =============================================================================
   Written by David Sha.
============================================================================= */