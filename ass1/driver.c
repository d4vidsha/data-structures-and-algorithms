#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "readin.h"
#include "data.h"
#include "linkedlist.h"

#define NUM_ARGS 3
#define STAGE_ARG_POS 1
#define DATA_FILENAME_ARG_POS 2
#define OUT_FILENAME_ARG_POS 3

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
    char *data_file = filename_strcpy(argv[DATA_FILENAME_ARG_POS]);
    char *out_file = filename_strcpy(argv[OUT_FILENAME_ARG_POS]);

    // access files
    FILE *data = fopen(data_file, "r");
    assert(data);
    FILE *out = fopen(out_file, "w");
    assert(out);

    // add footpath segments to a linked list
    list_t *list = create_empty_list();
    skip_header_line(data);
    build_list(data, list);

    // free everything
	free(data_file);
	free(out_file);

    return EXIT_SUCCESS;
}