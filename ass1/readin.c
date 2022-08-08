/* =============================================================================
   Project: dict1
   readin.h :
            = related all to reading from input
============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "readin.h"

/*  Copies specified argument to `filename` string. This includes a malloc.
    Ideally, every time this function is run, an associated `free(filename)`
    is to be included.
*/
char *filenamecpy(char *arg) {
    int filename_len = strlen(arg) + NULLBYTE;
    char *filename = (char *)malloc(sizeof(char) * filename_len);
    assert(filename);
    strcpy(filename, arg);
    return filename;
}

/* =============================================================================
   Written by David Sha.
============================================================================= */