/* Skeleton for W2.4, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  driver.c : 
             = the main program of the project 
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ADD: needed .h
#include "data.h"
#include "array.h"

// FILL IN THE CONTENT, MOSTLY BY COPYING FROM students.c
int main(int argc, char *argv[]) {
	student_t *students[MAX_STUDENTS];  // An array of "pointers to student_t"
	int n = 0;   /* Number of students */
	
	n = buildStudentArray(students);

	printStudentArray(students, n);

	printf("A student with highest score:\n");
	printStudent(bestStudent(students, n));

	/* CHANGED */
	printf("\nMemory used: %ld KB\n\n", bytesUsedByArray(students, n) >> 10);

	freeMemory(students, n);
	return EXIT_SUCCESS;
}


/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 05/07/2022
   ================================================================== */
