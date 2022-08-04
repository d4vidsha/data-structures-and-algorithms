/* Skeleton for W2.5, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  driver.c : 
             = the main program of the project 
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "array.h"

#define NUM_ARGS 3

int main(int argc, char *argv[]) {
	// FILL IN: check to have at least 3 arguments in command line
	//          open input and output files
	if (argc < NUM_ARGS) {
		printf("Error: Need at least %d arguments.\n", NUM_ARGS);
		return EXIT_FAILURE;
	}

	// printf("%s\n%s\n", argv[1], argv[2]);

	char *inFilename = (char *)malloc((strlen(argv[1]) + 1) * sizeof(char));
	assert(inFilename);
	char *outFilename = (char *)malloc((strlen(argv[2]) + 1) * sizeof(char));
	assert(outFilename);
	strcpy(inFilename, argv[1]);
	strcpy(outFilename, argv[2]);
	FILE *inFile = fopen(inFilename, "r");
	FILE *outFile = fopen(outFilename, "w");
	free(inFilename);
	free(outFilename);

	student_t *students[MAX_STUDENTS];
	           // students now is an array of pointers to struct 
	int n = 0;   // number of students 
	
	// FILL IN: some of the lines below need to be changed
	n = buildStudentArray(inFile, students);

	printStudentArray(outFile, students, n);

	fprintf(outFile, "A student with highest score:\n");
	printStudent(outFile, bestStudent(students, n));

	// prints out the memory in KB
	fprintf(outFile, "\nMemory used: %d KB\n\n", bytesUsedByArray(students, n) >> 10);

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
