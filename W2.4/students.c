/* Skeleton for W2.4, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
students.c: 
  Reads and prints a .csv file, and:
		- builds an array of pointers to data
		- uses library function strdup to duplicate strings 

  The Task: This file is a correct program.
            You should use it to break into modules as required 

  Expected Usage: ./students < input_CSV_file 
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
	char *name;       
	double score1;
	double score2;
	double totalScore;
};
typedef struct student student_t;

student_t *readStudent();
void printStudent(student_t *s);
int buildStudentArray(student_t *A[]);
void printStudentArray(student_t *A[], int n); 
student_t *bestStudent(student_t *A[], int n);
size_t bytesUsedByArray(student_t *A[], int n);
void freeMemory(student_t *A[], int n);

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
   Last Updated: 29/07/2022
   ================================================================== */


