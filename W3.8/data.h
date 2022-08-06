/* Skeleton for W3.8, comp20003 workshop Week 3 */

/*-------------------------------------------------------------- 
..Project: qStud
  data.h :  
         = the interface of module data of the project
----------------------------------------------------------------*/

#ifndef _DATA_H_
#define _DATA_H_
#include <stdio.h>

// constant defnitions
#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 512

// data definitions
typedef struct student student_t;

/*------------ function definitions -----------------------------*/

// skip the header line of .csv file "f"
void studentSkipHeaderLine(FILE *f);

// reads a student from file "f" to build a student_t data
// returns the pointer, or NULL if reading is unsuccessful
student_t *studentRead(FILE *f);

// prints the header line for the list of students
void studentPrintHeader(FILE *f);

// prints a student record *s to file "f"
void studentPrint(FILE *f, student_t *s);

// compares 2 student "a" and "b" by totalScore
// returns -1 if "a" is less than "b" by totalScore
// return 0 or +1 if "a" is equal to or greater than "b" 
int studentCompare(student_t *a, student_t *b);

// compares 2 student "a" and "b" by id, returns -1, 0, +1 for <, =, >  
int studentCmpID(student_t *a, student_t *b);

//returns bytes used by "*s"
size_t studentBytesUsed(student_t *s);

// free the memory allocated to a student "s"
void studentFree(student_t *s);

// returns id of a student
int studentGetID(student_t *s);

#endif



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 11/07/2022
   ================================================================== */
