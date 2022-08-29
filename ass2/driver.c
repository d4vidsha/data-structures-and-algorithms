/* =============================================================================
   Project: Assignment 1
   driver.c :
            = the main program of the project
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "driver.h"
#include "copy.h"
#include "linkedlist.h"
#include "readcsv.h"
#include "stage.h"

/*  This main function contains both stage 1 and stage 2.
*/
int main(int argc, char *argv[]) {

    // check if there is a stage argument specified
    if (argc <= 1) {
        fprintf(stderr, "ERROR: no input arguments provided\n\n");
        exit_failure_with_man();
    }
    int stage = atoi(argv[STAGE_ARG_POS]);

    // for the given stage, check if the number of arguments are consistent
    // with the stage
    if (stage == 1 || stage == 2) {
        if (!num_args_match(NUM_ARGS_1, argc)) {
            exit_failure_with_man();
        };
    } else (stage == 3 || stage == 4) {
        if (!num_args_match(NUM_ARGS_2, argc)) {
            exit_failure_with_man();
        }
    }

    // store all required arguments for all stages
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
    } else if (stage == 3 || stage == 4) {
        // store all extra arguments specific to stage 3 and 4
        long double xbl, ybl, xtr, ytr;
        xbl = strtold(argv[XBL_ARG_POS]);
        ybl = strtold(argv[YBL_ARG_POS]);
        xtr = strtold(argv[XTR_ARG_POS]);
        ytr = strtold(argv[YTR_ARG_POS]);
        if (stage == 3) {
            stage3(in, out, );
        } else {
            stage4(in, out, );
        }
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

/*  Prints the manual which contains usage examples to a file `f`. `f` is used
    mainly for `stderr`.
*/
void print_man(FILE *f) {
    fprintf(f,
        "USAGE:\n"
        "Argument examples for stages 1-4\n"
        " - 1 dataset.csv output.txt\n"
        " - 2 dataset.csv output.txt\n"
        " - 3 dataset.csv output.txt 144.9375 -37.8750 145.0000 -37.6875\n"
        " - 4 dataset.csv output.txt 144.9375 -37.8750 145.0000 -37.6875\n"
    );

}

/*  Checks if number of arguments `num_args` equals `argc`. Prints important
    info if `num_args` does not equal `argc`.
*/
int num_args_match(int num_args, int argc) {
    if (argc != num_args + 1) {
        if (argc > num_args + 1) {
            fprintf(stderr, "ERROR: too many arguments\n");
        } else if (argc < NUM_ARGS_1 + 1) {
            fprintf(stderr, "ERROR: too few arguments\n");
        }
        return FALSE;
    }
    return TRUE;
}

/*  Exit program as failed with manual printed to `stderr`.
*/
void exit_failure_with_man() {
    print_man(stderr);
    exit(EXIT_FAILURE);
}

/* =============================================================================
   Written by David Sha.
============================================================================= */