/* =============================================================================
   Project: Assignment 1
   driver.c :
            = the main program of the project
============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "readin.h"
#include "linkedlist.h"
#include "readcsv.h"
#include "stage.h"

#define NUM_ARGS 3
#define STAGE_ARG_POS 1
#define IN_FILENAME_ARG_POS 2
#define OUT_FILENAME_ARG_POS 3

/*  This main function contains both stage 1 and stage 2.
*/
int main(int argc, char *argv[]) {

    // ensure exactly `NUM_ARGS` arguments
    if (argc != NUM_ARGS + 1) {
        if (argc > NUM_ARGS + 1) {
            fprintf(stderr, "ERROR: too many arguments\n");
        } else if (argc < NUM_ARGS + 1) {
            fprintf(stderr, "ERROR: too few arguments\n");
        }
        exit(EXIT_FAILURE);
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

    // choose which stage to run
    if (stage == 1) {
        stage1(in, out);
    } else if (stage == 2) {
        stage2(in, out);
    } else {
        fprintf(stderr, "ERROR: invalid stage");
        exit(EXIT_FAILURE);
    }
    
    // free and close everything
    fclose(in);
    fclose(out);
    free(in_file);
	free(out_file);

    return EXIT_SUCCESS;
}

/* =============================================================================
   Written by David Sha.
============================================================================= */