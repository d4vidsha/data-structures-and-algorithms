/* Skeleton for W2.4, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
students.c: 
  Reading and printing a .csv file, and:
		- build an array of pointers to data
		- use library function strdup to duplicate strings 

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

struct student *readStudent();
void printStudent(struct student *s);
int buildStudentArray(struct student *A[]);
void printStudentArray(struct student *A[], int n); 
struct student *bestStudent(struct student *A[], int n);
size_t getBytesUsed(struct student *A[], int n);
void freeMemory(struct student *A[], int n);

int main(int argc, char *argv[]) {
	struct student *students[MAX_STUDENTS];  // an array of "pointers to struct student"
	int n=0;   /* number of students */
	
	n= buildStudentArray(students);

	printStudentArray(students, n);

	printf("A student with highest score:\n");
	printStudent( bestStudent(students, n));

	/* CHANGED */
	printf("\nMemory used: %ld KB\n\n", getBytesUsed(students, n) >> 10);

	freeMemory(students, n);
	return EXIT_SUCCESS;
}

// free the memory which was dynamically allocated for array A 
void freeMemory(struct student *A[], int n) {
	// since only A[i].name were dynamically allocated, 
	// we just need to free them 
	for (int i=0; i<n; i++) {
		free(A[i]->name);  // "name" was implicitly malloc-ed by the calling to function strdup
		free(A[i]);       // A[i] was malloc-ed when reaing a new student
	}
}


/* CHANGED: NEW FUNCTION HERE */
// returns bytes used by array A
size_t getBytesUsed(struct student *A[], int n) {
	int bytesUsed= MAX_STUDENTS * sizeof(struct student);
	for (int i=0; i<n; i++) {
		// adding the space used by each student's name and struct student
		bytesUsed += strlen(A[i]->name) + 1 + sizeof(struct student);
	}
	return bytesUsed;
}


// build a student from stdin, return pointer 
// returns NULL if data input unsuccessful 
struct student *readStudent() {
	int id;
	double score1, score2;
	char name[MAX_NAME_LEN+1];
	if (scanf("%d, %[^,], %lf , %lf", &id, name, &score1, &score2)==4) {
		struct student *s= malloc(sizeof(*s));
		assert(s);
		s->id= id;
		s->name= strdup(name);   // strdup allocates memory for s->name using malloc!
		s->score1= score1;
		s->score2= score2;
		s->totalScore= score1+score2;
		return s;
	}
	return NULL;
}

// prints a student record *s to stdout
void printStudent(struct student *s) {
	printf("%5d %-20s %6.1lf %6.1lf %6.1lf\n",
	        s->id, s->name, s->score1, s->score2, s->totalScore);
} 

// read data from stdin, builds array of pointers to "struct student",
//   and returns the number of students 
int buildStudentArray(struct student *A[]) {
	int n;
	char line[MAX_LINE_LEN+1];
	
	// gets rid of the header line
	scanf("%[^\n] ", line);
	// we can also use: while (getchar()!='\n');

	// reads and stores students in array students
	struct student *s;
	for (n=0; n<MAX_STUDENTS && ( s=readStudent() ) ; n++) {
		A[n]= s;
	}
	return n;
}

// prints the array of students
void printStudentArray(struct student *A[], int n) {
	int i;
	
	// prints the header line
	printf("STUDENT LIST\n");
	// the format string below is reproduced from the one in printStudent
	printf("%-5s %-20s %6s %6s %6s\n",
	        "ID", "Name", "score1", "score2", "total"); 

	
	// prints all students
	for (i=0; i<n; i++) {
		printStudent(A[i]);    // note that here A[i] is a pointer already
	}

	// prints end line
	// the series of numbers here is taken from the format string
	for (i=0; i<5+20+6+6+6+4; i++) printf("=");
	printf("\n\n"); 
}

// returns pointer to student with higest total score
// on tie, returns the one with lowest index
struct student *bestStudent(struct student *A[], int n) {
	struct student *max= A[0];    // max= pointer to the first student
	for (int i=1; i<n; i++) {
		if (A[i]->totalScore > max->totalScore)
			max= A[i];            // A+i is same as &A[i]
	}
	return max;
}

/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 05/07/2022
   ================================================================== */


