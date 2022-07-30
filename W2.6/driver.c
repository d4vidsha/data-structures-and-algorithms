/* Skeleton for W2.6, comp20003 workshop Week 2 */

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

#define FIRST 5   /* when outputting student list, only the top FIRST */
#define LAST 5    /* and the last LAST records are outputted          */ 

int main(int argc, char *argv[]) {
	// make sure to have at least 3 tokens in the command line 
	if (argc < 3) {
		fprintf(stderr, "Usage: %s input_file_name output_file_name\n", argv[0]);
		exit(EXIT_FAILURE);
	}   

	// opens input and output file, making sure that 
	//   the filenames given in the command line are valid
	FILE *inFile  = fopen(argv[1], "r"),
		 *outFile = fopen(argv[2], "w");
	assert(inFile && outFile);          // exit if fails to open files

	array_t *students = arrayCreate();   // "students" is a dynamic array
	
	// reads students from inFile and builds array
	studentSkipHeaderLine(inFile);
	student_t *s;
	while ((s = studentRead(inFile))) {
		arrayAppend(students, s);
	}
	fclose(inFile);

	// shrinks array to free the un-used space
	arrayShrink(students);

	arrayPrint(outFile, students, FIRST, LAST);

	fprintf(outFile, "A student with highest score:\n");
	studentPrint(outFile, bestStudent(students));

	fprintf(outFile, "\nMemory used: %ld Bytes\n\n", arrayBytesUsed(students));

	arrayFree(students);
	fclose(outFile);

	return 0;
}



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 06/07/2022
   ================================================================== */
