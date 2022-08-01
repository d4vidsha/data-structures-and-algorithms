/* Skeleton for W2.4, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  data.c :  
         = the implementation of module data of the project
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// ADD: needed .h
#include "data.h"

// FILL IN THE CONTENT, MOSTLY BY COPYING FROM students.c
struct student {
	int id;
	char *name;       
	double score1;
	double score2;
	double totalScore;
};

// build a student from stdin, return pointer 
// returns NULL if data input unsuccessful 
student_t *readStudent() {
	int id;
	double score1, score2;
	char name[MAX_NAME_LEN + 1];
	if (scanf("%d, %[^,], %lf , %lf", &id, name, &score1, &score2) == 4) {
		student_t *s = malloc(sizeof(*s));
		assert(s);
		s->id = id;
		s->name = strdup(name);   // strdup allocates memory for s->name using malloc!
		s->score1 = score1;
		s->score2 = score2;
		s->totalScore = score1 + score2;
		return s;
	}
	return NULL;
}

// prints a student record *s to stdout
void printStudent(student_t *s) {
	printf("%5d %-20s %6.1lf %6.1lf %6.1lf\n",
	        s->id, s->name, s->score1, s->score2, s->totalScore);
} 

/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 05/07/2022
   ================================================================== */

