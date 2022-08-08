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

char *filenamecpy(char *arg);

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

    stage = atoi(argv[STAGE_ARG_POS]);
    data_filen = filenamecpy(argv[DATA_FILENAME_ARG_POS]);
    out_filen = filenamecpy(argv[OUT_FILENAME_ARG_POS]);

    printf("%d %s %s\n", stage, data_filen, out_filen);

    // FILE *data_file = fopen(data_filen, "r");
	// FILE *out_file = fopen(out_filen, "w");

    // free everything
	free(data_filen);
	free(out_filen);

    return EXIT_SUCCESS;
}

/*  Copies specified argument to `filename` string. This includes a malloc.
    Ideally, every time this function is run, an associated `free(filename)`
    must be included.
*/
char *filenamecpy(char *arg) {
    int filename_len = strlen(arg) + NULLBYTE;
    char *filename = (char *)malloc(sizeof(char) * filename_len);
    assert(filename);
    strcpy(filename, arg);
    return filename;
}