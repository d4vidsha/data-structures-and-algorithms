/* Skeleton for W3.7, comp20003 workshop Week 3 */

/*-------------------------------------------------------------- 
..Project: qStud
  data.c :  
         = the implementation of module data of the project
----------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"

// The details of "struct student" is visible only inside "data.c"
// and cannot be accessed in any other modules 
struct student {
	int id;
	char *name;     // to facilitate strings with variable length
	double score1;
	double score2;
	double totalScore;
};

// skip the header line of .csv file "f"
void studentSkipHeaderLine(FILE *f) {
	while (fgetc(f) != '\n');
}

// reads a student from file "f" to build a student_t data.
// returns the pointer, or NULL if reading is unsuccessful.
student_t *studentRead(FILE *f) {
	student_t *s= NULL;
	int id;
	double score1, score2;
	char name[MAX_NAME_LEN + 1];

	if (fscanf(f, "%d, %[^,], %lf , %lf", &id, name, &score1, &score2) == 4) {
		s = malloc(sizeof(*s));     // allocates memory for s
		assert(s);
		s->id = id;
		s->name = strdup(name);     // duplicates strings name top s->name
		assert(s->name);            // (function strdup also does malloc) 
		s->score1 = score1;
		s->score2 = score2;
		s->totalScore = score1 + score2;
	}
	return s;
}

// prints a student record *s to file "f"
void studentPrint(FILE *f, student_t *s) {
	fprintf(f, "%5d %-20s %6.1lf %6.1lf %6.1lf\n",
	        s->id, s->name, s->score1, s->score2, s->totalScore);
} 

// prints the header line for the list of students
void studentPrintHeader(FILE *f) {
	// prints the header line
	fprintf(f, "STUDENT LIST\n");
	// the format string below is reproduced from the one in studentPrint
	fprintf(f, "%-5s %-20s %6s %6s %6s\n",
	        "ID", "Name", "score1", "score2", "total"); 
}

// compares 2 student "a" and "b" by totalScore
// returns -1 if "a" is less than "b" by totalScore
// return 0 or +1 if "a" is equal to or greater than "b" 
int studentCompare(student_t *a, student_t *b) {
	if (a->totalScore < b->totalScore) return -1;
	if (a->totalScore > b->totalScore) return +1;
	return 0;
}

//returns bytes used by "*s"
size_t studentBytesUsed(student_t *s) {
	return sizeof(*s) + strlen(s->name) + 1;
}

// free the memory allocated to a student "s"
void studentFree(student_t *s) {
	free(s->name);
	free(s);
}

// returns id of a student
int studentGetID(student_t *s) {
	return s->id;
	// note: better if we check "s" for not NULL first
}

/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 11/07/2022
   ================================================================== */
