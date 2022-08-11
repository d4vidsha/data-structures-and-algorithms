/* =============================================================================
   Project: Assignment 1
   readcsv.c :
            = related all to reading from .csv file
============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "readcsv.h"

int is_in_cell_length(int curr, int max) {
    if (curr >= max) {
        fprintf(stderr, "NOTE: CSV cell exceeds %d characters.\n", max);
        fprintf(stderr, "NOTE: Keeping only first %d characters.\n", max);
        return FALSE;
    }
    return TRUE;
}

void get_str(FILE *f, char *string) {
    int i = 0;
    int c;
    c = fgetc(f);
    if (c == DOUBLEQUOTE) {
        // is a special string
        while ((c = fgetc(f)) != DOUBLEQUOTE) {
            string[i] = c;
            i++;
            if (!is_in_cell_length(i, MAX_STR_LEN)) {
                break;
            }
        }
        // expect the next character to be a comma or newline or EOF
        if ((c = fgetc(f)) != COMMA  && c != NEWLINE && c != EOF) {
            fprintf(stderr, "ERROR: csv is poorly formatted (\"\"%c)\n", c);
            exit(EXIT_FAILURE);
        }
    } else if (c == COMMA || c == NEWLINE || c == EOF) {
        // is an empty string
    } else {
        // is a normal string
        string[i] = c;
        i++;
        if (is_in_cell_length(i, MAX_STR_LEN)) {
            while ((c = fgetc(f)) != COMMA && c != NEWLINE && c != EOF) {
                string[i] = c;
                i++;
                if (!is_in_cell_length(i, MAX_STR_LEN)) {
                    break;
                }
            }
        }
    }
    string[i] = NULLBYTE;
}

int get_int(FILE *f) {
    char temp[MAX_STR_LEN + NULLBYTE_LEN];
    get_str(f, temp);
    int value = atoi(temp);
    return value;
}

double get_double(FILE *f) {
    char temp[MAX_STR_LEN + NULLBYTE_LEN];
    char *ptr;
    get_str(f, temp);
    double value = strtod(temp, &ptr);
    return value;
}

/*  Skip header line from a .csv file `f`.
*/
void skip_header_line(FILE *f) {
    while(fgetc(f) != NEWLINE);
}

/*  Given a filename `f`, read a row into `fp` of type `footpath_segment_t`.
    Returns the pointer to malloc'd `fp`.
*/
footpath_segment_t *footpath_read_line(FILE *f) {
    footpath_segment_t *fp = NULL;
    fp = (footpath_segment_t *)malloc(sizeof(*fp));
    assert(fp);
    fp->footpath_id = get_int(f);
    get_str(f, fp->address);
    get_str(f, fp->clue_sa);
    get_str(f, fp->asset_type);
    fp->deltaz = get_double(f);
    fp->distance = get_double(f);
    fp->grade1in = get_double(f);
    fp->mcc_id = get_int(f);
    fp->mccid_int = get_int(f);
    fp->rlmax = get_double(f);
    fp->rlmin = get_double(f);
    get_str(f, fp->segside);
    fp->statusid = get_int(f);
    fp->streetid = get_int(f);
    fp->street_group = get_int(f);
    fp->start_lat = get_double(f);
    fp->start_lon = get_double(f);
    fp->end_lat = get_double(f);
    fp->end_lon = get_double(f);
    return fp;
}

/* =============================================================================
   Written by David Sha.
============================================================================= */