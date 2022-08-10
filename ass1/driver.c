#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "readin.h"
#include "data.h"
#include "linkedlist.h"
#include "readcsv.h"

#define NUM_ARGS 3
#define STAGE_ARG_POS 1
#define IN_FILENAME_ARG_POS 2
#define OUT_FILENAME_ARG_POS 3
#define NEWLINE_LEN 1
#define NOTFOUND "NOTFOUND"

int main(int argc, char *argv[]) {

    // ensure exactly `NUM_ARGS` arguments
    if (argc != NUM_ARGS + 1) {
        if (argc > NUM_ARGS + 1) {
            fprintf(stderr, "ERROR: too many arguments\n");
        } else if (argc < NUM_ARGS + 1) {
            fprintf(stderr, "ERROR: too few arguments\n");
        }
        return EXIT_FAILURE;
    }

    // store arguments
    int stage = atoi(argv[STAGE_ARG_POS]);
    char *in_file = filename_strcpy(argv[IN_FILENAME_ARG_POS]);
    char *out_file = filename_strcpy(argv[OUT_FILENAME_ARG_POS]);

    // access files
    FILE *in = fopen(in_file, "r");
    assert(in);
    FILE *out = fopen(out_file, "w");
    assert(out);

    // read footpath segments to a linked list
    list_t *list = create_empty_list();
    skip_header_line(in);
    build_list(in, list);

    // process queries on the fly
    char line[MAX_STR_LEN + NEWLINE_LEN + NULLBYTE];
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
    fclose(in);
    fclose(out);
	free(in_file);
	free(out_file);
    free_list(list);
    

    return EXIT_SUCCESS;
}

/* =============================================================================
   Written by David Sha.
   - Read line-by-line from stdin: https://stackoverflow.com/a/9206332/15444163
   - Remove newline from fgets: https://stackoverflow.com/a/28462221/15444163
============================================================================= */