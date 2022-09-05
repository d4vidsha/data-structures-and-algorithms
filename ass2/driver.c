/* =============================================================================
   Project: Assignment 2 (altered from Assignment 1)
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
#include "quadtree.h"
#include "print.h"

/*  This main function contains both stage 1 and stage 2.
*/
int main(int argc, char *argv[]) {

    // check if there is a stage argument specified
    if (argc <= 1) {
        fprintf(stderr, "ERROR: no input arguments provided\n\n");
        exit_failure_with_man();
    }
    int stage = atoi(argv[STAGE_ARG_POS]);

    // for the given stage, check if th stage is valid and the number of 
    // arguments are consistent with the stage
    if (stage == 1 || stage == 2) {
        if (!num_args_match(NUM_ARGS_1, argc)) {
            exit_failure_with_man();
        };
    } else if (stage == 3 || stage == 4) {
        if (!num_args_match(NUM_ARGS_2, argc)) {
            exit_failure_with_man();
        }
    } else {
        fprintf(stderr, "ERROR: invalid stage");
        exit(EXIT_FAILURE);
    }

    // store all required arguments for all stages
    char *in_file = filename_strcpy(argv[IN_FILENAME_ARG_POS]);
    char *out_file = filename_strcpy(argv[OUT_FILENAME_ARG_POS]);

    // access files
    FILE *in = fopen(in_file, "r");
    assert(in);
    free(in_file);
    FILE *out = fopen(out_file, "w");
    assert(out);
	free(out_file);

    // read footpath segments to a linked list
    list_t *list = create_empty_list();
    skip_header_line(in);
    build_list(in, list);
    fclose(in);

    // choose which stage to run, knowing that there can only be four stages
    if (stage == 1) {
        stage1(out, list);
    } else if (stage == 2) {
        stage2(out, list);
    } else if (stage == 3 || stage == 4) {
        // store extra arguments into a region specific to stage 3 and 4
        rectangle2D_t *region = parse_rectangle(argv);

        // construct quadtree from linked list copying over all data from
        // linked list
        qtnode_t *tree = create_quadtree(list, region);

        // query on the fly from `stdin`
        if (stage == 3) {
            stage3(out, tree);
        } else {
            stage4(out, tree);
        }

        // free everything else
        free_quadtree(tree);
    }
    
    // free and close everything else
    free_list(NOT_HOLLOW, list);
    fclose(out);

    return EXIT_SUCCESS;
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

/*  Given the input arguments from command line, return the region
    specified by the input arguments.
*/
rectangle2D_t *parse_rectangle(char *argv[]) {
    rectangle2D_t *new;
    long double xbl, ybl, xtr, ytr;
    char *ptr;
    xbl = strtold(argv[XBL_ARG_POS], &ptr);
    ybl = strtold(argv[YBL_ARG_POS], &ptr);
    xtr = strtold(argv[XTR_ARG_POS], &ptr);
    ytr = strtold(argv[YTR_ARG_POS], &ptr);
    point2D_t *bl = create_point(xbl, ybl);
    point2D_t *tr = create_point(xtr, ytr);
    new = create_rectangle(bl, tr);
    free_point(bl);
    free_point(tr);
    return new;
}

/* =============================================================================
   Written by David Sha.
============================================================================= */