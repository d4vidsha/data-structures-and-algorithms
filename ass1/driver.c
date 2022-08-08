#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STR_LEN 128
#define NUM_ARGS 3
#define NULLBYTE 1
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
    char *data_filen;
	char *out_filen;

    stage = argv[STAGE_ARG_POS];

    int data_filen_len = strlen(argv[DATA_FILENAME_ARG_POS]) + NULLBYTE;
    int out_filen_len = strlen(argv[OUT_FILENAME_ARG_POS]) + NULLBYTE;

    data_filen = (char *)malloc(sizeof(char) * data_filen_len);
	assert(data_filen);
    out_filen = (char *)malloc(sizeof(char) * out_filen_len);
	assert(out_filen);

	strcpy(data_filen, argv[DATA_FILENAME_ARG_POS]);
	strcpy(out_filen, argv[OUT_FILENAME_ARG_POS]);
	
    // FILE *inFile = fopen(inFilename, "r");
	// FILE *outFile = fopen(outFilename, "w");
	// free(inFilename);
	// free(outFilename);

    return EXIT_SUCCESS;
}