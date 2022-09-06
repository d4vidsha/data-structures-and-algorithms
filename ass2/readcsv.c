/* =============================================================================
   Project: Assignment 2 (imported from Assignment 1)
   readcsv.c :
            = related all to reading from .csv file
============================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "readcsv.h"

/*  When creating strings, check if we still have space to continue.
*/
int is_in_cell_length(int curr, int max) {
    if (curr >= max) {
        fprintf(stderr, "NOTE: CSV cell exceeds %d characters.\n", max);
        fprintf(stderr, "NOTE: Keeping only first %d characters.\n", max);
        return FALSE;
    }
    return TRUE;
}

/*  Given a .csv file `f`, write cell to the `string`. This function supports
    CSV cells with double quotes.
*/
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

/*  Given a .csv file `f`, write cell into an integer.
*/
int get_int(FILE *f) {
    char temp[MAX_STR_LEN + NULLBYTE_LEN];
    get_str(f, temp);
    int value = atoi(temp);
    return value;
}

/*  Given a .csv file `f`, write cell into a double.
*/
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

char *get_strdup(FILE *f) {
    char str[MAX_STR_LEN + NULLBYTE_LEN];
    get_str(f, str);
    char *strduped = strdup(str);
    assert(strduped);
    return strduped;
}

/*  Given a filename `f`, read a row into `fp` of type `footpath_segment_t`.
    Returns the pointer to malloc'd `fp`.
*/
footpath_segment_t *footpath_read_line(FILE *f) {
    footpath_segment_t *fp = NULL;
    fp = (footpath_segment_t *)malloc(sizeof(*fp));
    assert(fp);
    fp->footpath_id = get_int(f);
    fp->address = get_strdup(f);
    fp->clue_sa = get_strdup(f);
    fp->asset_type = get_strdup(f);
    fp->deltaz = get_double(f);
    fp->distance = get_double(f);
    fp->grade1in = get_double(f);
    fp->mcc_id = get_int(f);
    fp->mccid_int = get_int(f);
    fp->rlmax = get_double(f);
    fp->rlmin = get_double(f);
    fp->segside = get_strdup(f);
    fp->statusid = get_int(f);
    fp->streetid = get_int(f);
    fp->street_group = get_int(f);
    fp->start_lat = get_double(f);
    fp->start_lon = get_double(f);
    fp->end_lat = get_double(f);
    fp->end_lon = get_double(f);
    return fp;
}

void free_footpath(footpath_segment_t *fp) {
    free(fp->address);
    free(fp->clue_sa);
    free(fp->asset_type);
    free(fp->segside);
    free(fp);
}

/* =============================================================================
   Written by David Sha.
============================================================================= */