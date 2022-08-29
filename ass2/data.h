/* =============================================================================
   Project: Assignment 1
   data.h :
            = includes the footpath_segment struct used over multiple files
              
              this is also where all the #defines lie

              ensure that "data.h" is #included in all modules
============================================================================= */
#ifndef _DATA_H_
#define _DATA_H_

/* #defines ================================================================= */

// readcsv.c
#define COMMA ','
#define DOUBLEQUOTE '"'
#define NEWLINE '\n'
#define NULLBYTE '\0'
#define TRUE 1
#define FALSE 0

// stage.c
#define NOTFOUND "NOTFOUND"
#define NEWLINE_LEN 1            // length of newline

// readcsv.c stage.c
#define MAX_STR_LEN 128          // max string length

// copy.c readcsv.c stage.c
#define NULLBYTE_LEN 1           // size of nullbyte

// driver.c
#define NUM_ARGS 3               // number of arguments
#define STAGE_ARG_POS 1          // stage argument position
#define IN_FILENAME_ARG_POS 2    // input file argument position
#define OUT_FILENAME_ARG_POS 3   // output file argument position

// quicksort.c stage.c
#define COLUMN_INDEX_GRADE1IN 6  // grade1in column index

// quicksort.c
#define COLUMN_INDEX_ADDRESS 1   // address column index

// array.c
#define INIT_ARRAY_SIZE 2        // initial array size

/* structures =============================================================== */
typedef struct footpath_segment footpath_segment_t;
struct footpath_segment {
    int footpath_id;
    char address[MAX_STR_LEN + NULLBYTE_LEN];
    char clue_sa[MAX_STR_LEN + NULLBYTE_LEN];
    char asset_type[MAX_STR_LEN + NULLBYTE_LEN];
    double deltaz;
    double distance;
    double grade1in;
    int mcc_id;
    int mccid_int;
    double rlmax;
    double rlmin;
    char segside[MAX_STR_LEN + NULLBYTE_LEN];
    int statusid;
    int streetid;
    int street_group;
    double start_lat;
    double start_lon;
    double end_lat;
    double end_lon;
};

#endif
/* =============================================================================
   Written by David Sha.
============================================================================= */