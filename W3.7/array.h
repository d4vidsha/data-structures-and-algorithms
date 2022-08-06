/* Skeleton for W3.7, comp20003 workshop Week 3 */

/*-------------------------------------------------------------- 
..Project: qStud
  array.c : 
          = the interface of module array of the project
----------------------------------------------------------------*/

#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "data.h"

#define INIT_SIZE 2     // Initial size of arrays 

typedef struct array array_t;

// Creates & returns an empty array
array_t *arrayCreate();

// Free memory used by array "arr"
void arrayFree(array_t *arr);

// Inserts/appends data "s" to the end of array "arr" 
void arrayAppend(array_t *arr, student_t *s);

// Shrinks the array, to reduce array size to the same 
//    as the number of element used
void arrayShrink(array_t *arr);

// Returns pointer to student with highest total score
// on tie, returns the one with lowest index
student_t *bestStudent(array_t *arr);

// Prints the array of students to file "f"
// Prints only top "first" and bottom "last" students if array is big
void arrayPrint(FILE *f, array_t *arr, int first, int last);

// Returns memory used (in bytes) by the array 
size_t arrayBytesUsed(array_t *arr);

#endif



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 11/07/2022
   ================================================================== */
