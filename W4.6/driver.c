/* Skeleton for W4.6, comp20003 workshop Week 4 */


/*-------------------------------------------------------------- 
..Project: qStud
  driver.c : 
             = the main program of the project 
----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "data.h"
#include "array.h"
#include "list.h"

// used or potential data structures for dictionary 
#define ARRAY 1
#define SORTED_ARRAY 2
#define LINKED_LIST 3
#define BINARY_SEARCH_TREE 4
#define AVL 5
#define MIN_DS ARRAY           /* MIN_DS and MAX_DS define the range of              */
#define MAX_DS LINKED_LIST     /* data structures implemented in the current version */
static char *dictNames[] = {"NA", "array", "sorted_array", "linked_list",
                            "binary_search_tree", "AVL"};

#define OUTPUT_SEARCHES 10    /* number of detailed searches printed */

array_t *getStudentArray(char *filename, int dictType);
void arrayQuerying(char *dataFileName, FILE *inFile, FILE *outFILE, FILE *infoFILE, int dictType);

void listQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile, int dictType);

int processArgs(int argc, char *argv[]);
void outputStats(FILE *f, int nSuccess, int sComps, int nFailure, int fComps);

int main(int argc, char *argv[]) {
	int dictType = processArgs(argc, argv);

	FILE *infoFile = fopen(argv[3], "w");
	assert(infoFile);

	// runs respective query system
	switch (dictType) {
		case ARRAY:
		case SORTED_ARRAY:
			arrayQuerying(argv[2], stdin, stdout, infoFile, dictType);
			break;
		case LINKED_LIST:
			listQuerying(argv[2], stdin, stdout, infoFile, dictType);
			break;
		default:
			fprintf(stderr, "Dictionary type %d not yet implemented\n", dictType);
			exit(EXIT_FAILURE);
	}
	
	fclose(infoFile);

	return 0;
}

// makes sure to have enough arguments in the command line
// returns the specified dictionnary type
int processArgs(int argc, char *argv[]) {
	if (argc < 3 || atoi(argv[1]) < MIN_DS || atoi(argv[1]) > MAX_DS ) {
		fprintf(stderr, "Usage: %s dictionary_type input_file_name info_file_name, where:\n", argv[0]);
		fprintf(stderr, "       \t - dictionary_type can be:\n");
		for (int i = MIN_DS; i <= MAX_DS; i++)
			fprintf(stderr, "       \t\t %d for %s\n", i, dictNames[i]);
		fprintf(stderr, "       \t - input_file_name: data file for buiding dictionary\n");
		fprintf(stderr, "       \t - info_file_name: a file for outputing technical details of searches\n");
		exit(EXIT_FAILURE);
	}
	return atoi(argv[1]);
}

/*--------FUNCTIONS FOR WORKING WITH ARRAYS AND SORTED ARRAYS ----------------*/

// reads students from "filename", 
// returns array of students (for dictType=ARRAY)
//         or id-sorted array of students (for dictType=SORTED_ARRAY)
array_t *getStudentArray(char *filename, int dictType) {
	assert(dictType == ARRAY || dictType == SORTED_ARRAY);
	FILE *f = fopen(filename, "r");
	assert(f);
	array_t *students = arrayCreate();   // "students" is a dynamic array
	studentSkipHeaderLine(f);
	student_t *s;
	while ((s = studentRead(f)) ) {
		if (dictType == ARRAY) {
			arrayAppend(students, s);
		} else {
			sortedArrayInsert(students, s);
		}
	}
	fclose(f);
	arrayShrink(students);
	// uncomment the following line to print the array and check if it is sorted!
	// arrayPrint(stderr, students,5000,5000);
	return students;
}

// querying with student id,
// using sequential search if array is unsorted (dictType=ARRAY)
// using binary search if array is unsorted (dictType=SORTED_ARRAY)
void arrayQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile, int dictType) {
	assert(dictType == ARRAY || dictType == SORTED_ARRAY);

	// builds array of students
	array_t *students = getStudentArray(dataFileName, dictType);

	// Interactive Querying: get queries and perform sequential search
	int i = 0;                    /* search id, as one-origin integers         */
	int comps;                    /* number of comparisons used by search      */
	int nSuccess = 0, sComps = 0; /* total successful searches and comparisons */
	int nFailure = 0, fComps = 0; /* total failed     searches and comparisons */
	int dictSize;                 /* size of dictionary, i.e. elements in array*/

	int query;
	student_t *s = NULL;

	while (fscanf(inFile, "%d", &query) == 1) {
		i++;
		if (dictType == ARRAY) {
			s = arraySearch(students, query, &comps, &dictSize);
		} else {
			s = arrayBinarySearch(students, query, &comps, &dictSize);
		}
		if (i <= OUTPUT_SEARCHES) fprintf(outFile, "%d \t: ", query);
		if (s) {
			if (i <= OUTPUT_SEARCHES) {
				studentPrint(outFile, s);
				fprintf(infoFile, "#%d: SUCCESSFUL   \t%d \tcomparisons\n", i, comps);
			}
			nSuccess++;
			sComps += comps;
		} else {
			if (i <= OUTPUT_SEARCHES) {
				fprintf(outFile, "NOT FOUND\n");
				fprintf(infoFile, "#%d: UNSUCCESSFUL \t%d \tcomparisons\n", i, comps);
			}
			nFailure++;
			fComps += comps;
		}
	}
	
	if (i > OUTPUT_SEARCHES) {
		fprintf(outFile, ". . . . .\n");
		fprintf(infoFile, ". . . . .\n");
	}
	fprintf(infoFile, "\nSummary of searching in %s of %d elements:\n", 
	                  dictNames[dictType], dictSize);
	outputStats(infoFile, nSuccess, sComps, nFailure, fComps);

	arrayFree(students);
}

/*--------FUNCTIONS FOR OUTPUTING SEARCH DETAILS -----------------------*/

// outputs one line of statistics to file "f"
void outputLine(FILE *f, int searches, int comps, char *header) {
	fprintf(f, "%-12s: \t%d searches \t%d \tcomparisons \t%.0lf \tcomps/search\n",
	           header, searches, comps, ((double) comps) / searches);
}  

// ouputs search statistics to file "f"
void outputStats(FILE *f, int nSuccess, int sComps, int nFailure, int fComps) {
	outputLine(f, nSuccess + nFailure, sComps + fComps, "Total");
	outputLine(f, nSuccess, sComps, "Successful");
	outputLine(f, nFailure, fComps, "Unsuccessful");
}


/*--------FUNCTIONS FOR WORKING WITH LINKED LISTS  -------------------------*/

// reads students from "filename", 
// returns lined list of students
list_t *getStudentList(char *filename) {
	FILE *f = fopen(filename, "r");
	assert(f);
	list_t *students = listCreate();
	studentSkipHeaderLine(f);
	student_t *s;
	while ((s = studentRead(f))) {
		listAppend(students, s);
	}
	fclose(f);
	return students;
}


// querying with student id on linked list_t
// note that only sequentail search is available for linked lists
void listQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile, int dictType) {
	assert(dictType == LINKED_LIST);

	// builds array of students
	list_t *students = getStudentList(dataFileName);

	// Interactive Querying: get queries and perform sequential search
	int i= 0;                     /* search id, as one-origin integers         */
	int comps;                    /* number of comparisons used by search      */
	int nSuccess = 0, sComps = 0; /* total successful searches and comparisons */
	int nFailure = 0, fComps = 0; /* total failed     searches and comparisons */
	int dictSize;                 /* size of dictionary, i.e. elements in array */

	int query;
	student_t *s = NULL;

	while (fscanf(inFile, "%d", &query) == 1) {
		i++;
		s = listSearch(students, query, &comps, studentGetID);

		if (i <= OUTPUT_SEARCHES) fprintf(outFile, "%d \t: ", query);
		if (s) {
			if (i <= OUTPUT_SEARCHES) {
				studentPrint(outFile, s);
				fprintf(infoFile, "#%d: SUCCESSFUL   \t%d \tcomparisons\n", i, comps);
			}
			nSuccess++;
			sComps += comps;
		} else {
			if (i <= OUTPUT_SEARCHES) {
				fprintf(outFile, "NOT FOUND\n");
				fprintf(infoFile, "#%d: UNSUCCESSFUL \t%d \tcomparisons\n", i, comps);
			}
			nFailure++;
			fComps += comps;
		}
	}
	
	if (i > OUTPUT_SEARCHES) {
		fprintf(outFile, ". . . . .\n");
		fprintf(infoFile, ". . . . .\n");
	}

	dictSize = listCount(students);
	fprintf(infoFile, "\nSummary of searching in %s of %d elements:\n", 
	                  dictNames[dictType], dictSize);
	outputStats(infoFile, nSuccess, sComps, nFailure, fComps);

	listFree(students, studentFree);
}



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 15/07/2022
   ================================================================== */

