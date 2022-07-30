/* Skeleton for W2.5, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  driver.c : 
             = the main program of the project 
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "array.h"

int main(int argc, char *argv[]) {
	// FILL IN: check to have at least 3 arguments in command line
	//          open input and output files
	student_t *students[MAX_STUDENTS];
	           // students now is an array of pointers to struct 
	int n = 0;   // number of students 
	
	// FILL IN: some of the lines below need to be changed
	n = buildStudentArray(students);

	printStudentArray(students, n);

	printf("A student with highest score:\n");
	printStudent(bestStudent(students, n));

	// prints out the memory in KB
	printf("\nMemory used: %ld KB\n\n", bytesUsedByArray(students, n) >> 10);

	// free all the momory that were malloc-ed:
	freeStudentArray(students, n);

	// FILL IN: close the opened files!
	return EXIT_SUCCESS;
}



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 05/07/2022
   ================================================================== */
