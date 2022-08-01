/* Skeleton for W2.4, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  array.c :
          = the implementation of module array of the project
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ADD: needed .h
#include "array.h"

// FILL IN THE CONTENT, MOSTLY BY COPYING FROM students.c

// Free the memory which was dynamically allocated for array A 
void freeMemory(student_t *A[], int n) {
	// Since only A[i].name was dynamically allocated, 
	// we only need to free that field before freeing A[i] 
	for (int i = 0; i < n; i++) {
		free(A[i]->name);  // "name" was consequentially malloc-ed by the calling the function strdup
		free(A[i]);       // A[i] was malloc-ed when reading a new student
	}
}

/* CHANGED: NEW FUNCTION HERE */
// Returns bytes used by array A
size_t bytesUsedByArray(student_t *A[], int n) {
	int bytesUsed = MAX_STUDENTS * sizeof(student_t *);
	for (int i = 0; i < n; i++) {
		// Adding the space used by each student's name and student_t
		bytesUsed += strlen(A[i]->name) + 1 + sizeof(student_t);
	}
	return bytesUsed;
}

// Reads data from stdin, builds array of pointers to "student_t",
//   and returns the number of students 
int buildStudentArray(student_t *A[]) {
	int n;
	char line[MAX_LINE_LEN + 1];
	
	// Gets rid of the header line
	scanf("%[^\n] ", line);
	// We can also use: while (getchar() != '\n');

	// Reads and stores students in array students
	student_t *s;
	for (n = 0; n < MAX_STUDENTS && (s = readStudent()); n++) {
		A[n] = s;
	}
	return n;
}

// Prints the array of students
void printStudentArray(student_t *A[], int n) {
	int i;
	
	// Prints the header line
	printf("STUDENT LIST\n");
	// The format string below is reproduced from the one in printStudent
	printf("%-5s %-20s %6s %6s %6s\n",
	        "ID", "Name", "score1", "score2", "total"); 

	
	// Prints all students
	for (i = 0; i < n; i++) {
		printStudent(A[i]);    // note that here A[i] is a pointer already
	}

	// Prints end line
	// The series of numbers here is taken from the format string
	for (i = 0; i < 5 + 20 + 6 + 6 + 6 + 4; i++) printf("=");
	printf("\n\n"); 
}

// Returns pointer to student with higest total score
// on tie, returns the one with lowest index
student_t *bestStudent(student_t *A[], int n) {
	student_t *max = A[0];    // max = pointer to the first student
	for (int i = 1; i < n; i++) {
		if (A[i]->totalScore > max->totalScore)
			max = A[i];            // A + i is same as &A[i]
	}
	return max;
}

/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 05/07/2022
   ================================================================== */
