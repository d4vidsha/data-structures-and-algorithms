/* Skeleton for W3.8, comp20003 workshop Week 3 */

/*-------------------------------------------------------------- 
..Project: qStud
  array.c : 
          = the interface of module array of the project
----------------------------------------------------------------*/

#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "data.h"

#define INIT_SIZE 2     // initial size of arrays 
 
typedef struct array array_t;

// creates & returns an empty array
array_t *arrayCreate();

// free memory used by array "arr"
void arrayFree(array_t *arr);

// inserts/appends data "s" to the end of array "arr" 
void arrayAppend(array_t *arr, student_t *s);
// inserts data "s" into array "arr", ensuring "arr" is sorted 
void sortedArrayInsert(array_t *arr, student_t *s);


// shrinks the array, to reduce array size to the same 
//    as the number of element used
void arrayShrink(array_t *arr);

// returns pointer to student with highest total score
// on tie, returns the one with lowest index
student_t *bestStudent(array_t *arr);

// prints the array of students to file "f"
// prints only top "first" and bottom "last" students if array is big
void arrayPrint(FILE *f, array_t *arr, int first, int last);

// returns memory used (in bytes) by the array 
size_t arrayBytesUsed(array_t *arr);

// searches for student with "id" in array "arr"
// returns the pointer to the found student, NULL if not found
// also reports "*comps" - the number of key comparisons
//      and     "*dictSize" - the number of elements in array/dictionnary
student_t *arraySearch(array_t *arr, int id, int *comps, int *dictSize);

// searches for student with "id" in sorted array "arr"
// returns the pointer to the found student, NULL if not found
// also reports "*comps" - the number of key comparisons
//      and     "*dictSize" - the number of elements in array/dictionnary
student_t *arrayBinarySearch(array_t *arr, int id, int *comps, int *dictSize);

void arrayEnableInsert(array_t *arr);

#endif



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 11/07/2022
   ================================================================== */