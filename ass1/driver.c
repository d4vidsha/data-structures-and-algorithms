#include <stdio.h>
#include <stdlib.h>
#include "readin.h"

#define MAX_STR_LEN 128
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
    int stage;
    char *data_file;
	char *out_file;

    stage = atoi(argv[STAGE_ARG_POS]);
    data_file = filenamecpy(argv[DATA_FILENAME_ARG_POS]);
    out_file = filenamecpy(argv[OUT_FILENAME_ARG_POS]);

    printf("%d %s %s\n", stage, data_file, out_file);

    // FILE *data = fopen(data_file, "r");
	// FILE *out = fopen(out_file, "w");





    // free everything
	free(data_file);
	free(out_file);

    return EXIT_SUCCESS;
}