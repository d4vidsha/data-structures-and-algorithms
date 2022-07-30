/* Solution for W2.4, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  driver.c : 
             = the main progarm of the project 
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "array.h"

int main(int argc, char *argv[]) {
	student_t *students[MAX_STUDENTS];
	           // students now is an array of pointers to struct 
	int n = 0;   // number of students 
	
	n = buildStudentArray(students);

	printStudentArray(students, n);

	printf("A student with highest score:\n");
	printStudent( bestStudent(students, n));

	// prints out the memory in KB
	printf("Memory used: %d KB\n\n", memoryUsedByArray(students, n));

	// free all the momory that were malloc-ed:
	freeStudentArray(students, n);
	return EXIT_SUCCESS;
}



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 05/07/2022
   ================================================================== */
