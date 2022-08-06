/* Skeleton for W3.7, comp20003 workshop Week 3 */

/*-------------------------------------------------------------- 
..Project: qStud
  array.c :
          = the implementation of module array of the project
----------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "array.h"
#include "data.h"

struct array {
	student_t **A;      // use as array of student_t *, ie. student_t *A[]
	int size;           // current array size
	int n;              // current number of elements
};

// creates & returns an empty array
array_t *arrayCreate() {
	array_t *arr = malloc(sizeof(*arr));
	assert(arr);
	int size = INIT_SIZE;      // "size" used for convenience
	arr->size = size;
	arr->A = malloc(size * sizeof(*(arr->A)));
	assert(arr->A);
	arr->n = 0;
	return arr;
}

// free memory used by array "arr"
void arrayFree(array_t *arr) {
	for (int i = 0; i < arr->n; i++) {
		studentFree(arr->A[i]);
	}
	free(arr->A);
	free(arr);
}


// shrinks the array, to reduce array size to the same 
//    as the number of element used
void arrayShrink(array_t *arr) {
	if (arr->size != arr->n) {
		// the new size should be at least INIT_SIZE
		arr->size = arr->n > INIT_SIZE ? arr->n : INIT_SIZE;
		arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
		assert(arr->A);
	}
}


// makes sure that array's size exceeds its number of elements
//    ie. there is space for adding new element
void arrayEnsureSize(array_t *arr) {
	if (arr->n == arr->size) {
		arr->size <<= 1;       // same as arr->size *= 2;
		arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
		assert(arr->A);
	}
}

// inserts/appends data "s" to the end of array "arr" 
void arrayAppend(array_t *arr, student_t *s) {
	arrayEnsureSize(arr);
	arr->A[arr->n]= s;
	(arr->n)++;
}


// prints the array of students to file "f"
// prints only top "first" and bottom "last" students if array is big
void arrayPrint(FILE *f, array_t *arr, int first, int last) {
	int i;
	int longdotPrinted = (arr->n <= first + last) ? 1 : 0;

	studentPrintHeader(f);
	// prints all students
	for (i = 0; i < arr->n; i++) {
		if (! longdotPrinted && i == first) {
			fprintf(f, ". . . . .\n");
			longdotPrinted = 1;
		}
		if (i < first || i >= (arr->n - last))
			studentPrint(f, arr->A[i]);    // note that here A[i] is a pointer
	}

	fprintf(f, "\nThe list contains %d students\n", arr->n);
}

// returns memory used (in bytes) by the array 
size_t arrayBytesUsed(array_t *arr) {
	// 0. memory used for arr 
	size_t bytesUsed = sizeof(*arr);

	// 1. memory for the array of pointers 
	bytesUsed += arr->size * sizeof(student_t *);

	// 2. + memory for n elements
	for (int i = 0; i < arr->n; i++) {
		bytesUsed += studentBytesUsed(arr->A[i]);
	}

	// returns the memory in KB
	return bytesUsed;
}

// returns pointer to student with highest total score
// on tie, returns the one with lowest index
student_t *bestStudent(array_t *arr) {
	student_t *max = arr->A[0];    // max = pointer to the first student
	for (int i = 1; i < arr->n; i++) {
		if (studentCompare(arr->A[i], max) > 0)
			max = arr->A[i];            // A + i is same as &A[i]
	}
	return max;
}

/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 12/07/2022
   ================================================================== */
