/* Skeleton for W1.6, comp20003 workshop Week 1 */

/*-------------------------------------------------------------- 
w1.6.c:
  Reading and printing a .csv file, also use my own version of strdup

  The Task: 
		1. Discuss with your peers, fix function strDuplicate until 
			the program outputs seems reasonable
		2. Use valgrind and fix memory-related valgrind errors

  Expected Usage: ./w1.6 < input_CSV_file 
----------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 512
#define MAX_STUDENTS 5000

struct student {
	int id;
	char *name;       /* CHANGED */
	double score1;
	double score2;
	double totalScore;
};

int readStudent(struct student *s);
void printStudent(struct student *s);
int buildStudentArray(struct student A[]);
void printStudentArray(struct student A[], int n); 
struct student *bestStudent(struct student A[], int n);
int getBytesUsed(struct student A[], int n);   /* CHANGED */
void freeStudentArray(struct student A[], int n);

int main(int argc, char *argv[]) {
	struct student students[MAX_STUDENTS];
	int n = 0;   /* number of students */
	
	n = buildStudentArray(students);

	printStudentArray(students, n);

	printf("A student with highest score:\n");
	printStudent(bestStudent(students, n));

	/* CHANGED */
	printf("\nMemory used: %d KB\n\n", getBytesUsed(students, n) >> 10);

	freeStudentArray(students, n);

	return EXIT_SUCCESS;
}

void freeStudentArray(struct student A[], int n) {
	for (int i = 0; i < n; i++) {
		free(A[i].name);
	}
}

/* CHANGED: NEW FUNCTION HERE */
// returns bytes used by array A
int getBytesUsed(struct student A[], int n) {
	int bytesUsed = MAX_STUDENTS * sizeof(struct student);
	for (int i = 0; i < n; i++) {
		// adding the space used by each student's name
		// CHANGED, FILL IN: need to add bytes used by A[i].name to bytesUsed
		bytesUsed += (strlen(A[i].name) + 1);
	}
	return bytesUsed;
}

/* CHANGED: NEW FUNCTION HERE */
// returns a duplicate of a string, just similar to strdup
char *strDuplicate(const char *s) {
	// char duplicate[strlen(s) + 1];  // use just as many as needed bytes!
	char *duplicate; 
	duplicate = (char *) malloc(sizeof(char) * (strlen(s) + 1));
	assert(duplicate);
	char *p;

	for (p = duplicate; *s; *(p++) = *(s++));
	*p = '\0';
	return duplicate;
}

// reads a student from stdin to *s
// returns 1 if successful, 0 if not
int readStudent(struct student *s) {
	int id;
	double score1, score2;
	char name[MAX_NAME_LEN + 1];
	if (scanf("%d, %[^,], %lf , %lf", &id, name, &score1, &score2) == 4) {
		s->id = id;
		/* CHANGED */
		s->name = strDuplicate(name);
		s->score1 = score1;
		s->score2 = score2;
		s->totalScore = score1 + score2;
		return 1;
	}
	return 0;
}

// prints a student record *s to stdout
void printStudent(struct student *s) {
	printf("%5d %-20s %6.1lf %6.1lf %6.1lf\n",
	    s->id, s->name, s->score1, s->score2, s->totalScore);
} 

// read data from stdin, builds array of students,
//   and returns the number of students 
int buildStudentArray(struct student A[]) {
	int n;
	char line[MAX_LINE_LEN + 1];
	
	// gets rid of the header line
	scanf("%[^\n] ", line);
	// we can also use: while (getchar()!='\n');

	// reads and stores students in array students
	for (n = 0; n < MAX_STUDENTS && readStudent(&A[n]); n++);
	return n;
}

// prints the array of students
void printStudentArray(struct student A[], int n) {
	int i;
	
	// prints the header line
	printf("STUDENT LIST\n");
	// the format string below is reproduced from the one in printStudent
	printf("%-5s %-20s %6s %6s %6s\n",
	    "ID", "Name", "score1", "score2", "total"); 

	
	// prints all students
	for (i = 0; i < n; i++) {
		printStudent(&A[i]);
	}

	// prints end line
	// the series of numbers here is taken from the format string
	for (i = 0; i < 5 + 20 + 6 + 6 + 6 + 4; i++) printf("=");
	printf("\n\n"); 
}

// returns pointer to student with higest total score
// on tie, returns the one with lowest index
struct student *bestStudent(struct student A[], int n) {
	struct student *max = A + 0;    // A + 0 is A, and is &A[0]
	for (int i = 0; i < n; i++) {
		if (A[i].totalScore > max->totalScore)
			max = A + i;            // A + i is the same as &A[i]
	}
	return max;
}

/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 01/07/2022
   ================================================================== */


