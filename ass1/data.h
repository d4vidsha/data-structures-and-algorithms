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
#define NEWLINE '\n'
#define NUM_FIELDS 19
#define MAX_STR_LEN 128
#define NULLBYTE_LEN 1      // size of nullbyte
#define NUM_ARGS 3
#define STAGE_ARG_POS 1
#define IN_FILENAME_ARG_POS 2
#define OUT_FILENAME_ARG_POS 3
#define NEWLINE_LEN 1
#define NOTFOUND "NOTFOUND"
#define COMMA ','
#define DOUBLEQUOTE '"'
#define NULLBYTE '\0'
#define TRUE 1
#define FALSE 0
#define COLUMN_INDEX_GRADE1IN 6
#define COLUMN_INDEX_ADDRESS 1

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