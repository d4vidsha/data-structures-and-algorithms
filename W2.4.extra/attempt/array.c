/* Solution for W2.4, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  array.c :
          = the implementation of module array of the project
----------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "data.h"

// returns memory used (in KB) by the array 
int memoryUsedByArray(student_t *A[], int n) {

	// memory used for A[]:
	// 1. memory for the array of pointers 
	size_t bytesUsed = MAX_STUDENTS * sizeof(student_t *);

	// 2. + memory for n structs
	bytesUsed += n * sizeof(student_t);

	// 3. + memory for n names
	for (int i = 0; i < n; i++) {
		bytesUsed += strlen(A[i]->name) + 1;
	}

	// returns the memory in KB
	return bytesUsed >> 10;
}

// frees the dynamic memory allocated to elements of A[]
void freeStudentArray(student_t *A[], int n) {
	for (int i = 0; i < n; i++) {
		free(A[i]->name);      // free the memory malloc-ed by strdup
		free(A[i]);            // free the memory A[i] points to
	}
}

// read data from stdin, builds array of pointers to "student_t",
//   and returns the number of students 
int buildStudentArray(student_t *A[]) {
	int n;
	char line[MAX_LINE_LEN + 1];
	
	// gets rid of the header line
	scanf("%[^\n] ", line);
	// we can also use: while (getchar()!='\n');

	// reads and stores students in array students
	student_t *s;
	for (n = 0; n < MAX_STUDENTS && (s = readStudent()) ; n++) {
		A[n] = s;
	}
	return n;
}

// prints the array of students
void printStudentArray(student_t *A[], int n) {
	int i;
	
	// prints the header line
	printf("STUDENT LIST\n");
	// the format string below is reproduced from the one in printStudent
	printf("%-5s %-20s %6s %6s %6s\n",
	        "ID", "Name", "score1", "score2", "total"); 

	
	// prints all students
	for (i = 0; i < n; i++) {
		printStudent(A[i]);    // note that here A[i] is a pointer already
	}

	// prints end line
	// the series of numbers here is taken from the format string
	for (i = 0; i < 5 + 20 + 6 + 6 + 6 + 4; i++) printf("=");
	printf("\n\n"); 
}

// returns pointer to student with higest total score
// on tie, returns the one with lowest index
student_t *bestStudent(student_t *A[], int n) {
	student_t *max = A[0];    // max = pointer to the first student
	for (int i = 1; i < n; i++) {
		if (A[i]->totalScore > max->totalScore)
			max = A[i];            // A+i is same as &A[i]
	}
	return max;
}



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 05/07/2022
   ================================================================== */
