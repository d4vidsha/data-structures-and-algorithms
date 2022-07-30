/* Solution for W2.5, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  array.c : 
          = the interface of module array of the project
----------------------------------------------------------------*/


#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "data.h"

#define MAX_STUDENTS 5000

// reads data from file f, builds array of pointers to "student_t",
//   and returns the number of students 
int buildStudentArray(FILE *f, student_t *A[]);

// prints the array of students to file "f"
void printStudentArray(FILE *f, student_t *A[], int n); 

// returns pointer to student with higest total score
// on tie, returns the one with lowest index
student_t *bestStudent(student_t *A[], int n);

// frees the dynamic memory allocated to elements of A[]
void freeStudentArray(student_t *A[], int n);

// returns memory used (in bytes) by the array 
size_t bytesUsedByArray(student_t *A[], int n);

#endif



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 06/07/2022
   ================================================================== */
