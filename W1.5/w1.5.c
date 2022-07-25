/* Skeleton for W1.5, comp20003 workshop Week 1 */

/*-------------------------------------------------------------- 
w1.5.c:
  Reading and printing a .csv file, naive solution.

  The Task: Use valgrind/gdb to debug 

  Expected Usage: ./w1.5 < input_CSV_file 
----------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 512
#define MAX_STUDENTS 5000

struct student {
	int id;
	char name[MAX_NAME_LEN + 1];
	double score1;
	double score2;
	double totalScore;
};
typedef struct student student_t;


int readStudent(student_t *s);
void printStudent(student_t *s);
int buildStudentArray(student_t A[]);
void printStudentArray(student_t A[], int n); 
student_t *bestStudent(struct student A[], int n);

int main(int argc, char *argv[]) {
	student_t students[MAX_STUDENTS];
	int n = 0;   /* number of students */
	n = buildStudentArray(students);

	printStudentArray(students, n);

	printf("A student with highest score:\n");
	printStudent(bestStudent(students, n));

	int bytesUsed = MAX_STUDENTS * sizeof(student_t);
	printf("\nMemory used: %d KB\n\n", bytesUsed >> 10);

	return EXIT_SUCCESS;
}

// reads a student from stdin to *s
// returns 1 if successful, 0 if not
int readStudent(student_t *s) {
	int id;
	double score1, score2;
	char name[MAX_NAME_LEN + 1];

	if (scanf(" %d, %[^,], %lf , %lf", &id, name, &score1, &score2) == 4) {
		s->id = id;
		strcpy(s->name, name);
		s->score1 = score1;
		s->score2 = score2;
		s->totalScore = score1 + score2;
		return 1;
	}
	return 0;
}

// prints a student record *s to stdout
void printStudent(student_t *s) {
	printf("%5d %-20s %6.1lf %6.1lf %6.1lf\n", s->id, s->name, s->score1, 
		s->score2, s->totalScore);
} 

// read data from stdin, builds array of students,
//   and returns the number of students 
int buildStudentArray(student_t A[]) {
	int n;
	char line[MAX_LINE_LEN + 1];
	
	// gets rid of the header line
	scanf("%[^\n] ", line);
	// we can also use: while (getchar()!='\n');

	// reads and stores students in array students
	for (n = 0; n < MAX_STUDENTS && readStudent(&A[n]); n++);
	if (n == MAX_STUDENTS) {
		while (getchar() != EOF);
	}
	return n;
}

// prints the array of students
void printStudentArray(student_t A[], int n) {
	int i;
	
	// prints the header line
	printf("STUDENT LIST\n");
	// the format string below is reproduced from the one in printStudent
	printf("%-5s %-20s %6s %6s %6s\n",
	        "ID", "Name", "score1", "score2", "total"); 

	
	// prints all students
	for (i = 0; i <= n; i++) {
		printStudent(&A[i]);
	}

	// prints end line
	// the series of numbers here is taken from the format string
	for (i = 0; i < 5 + 20 + 6 + 6 + 6 + 4; i++) printf("=");
	printf("\n\n"); 
}

// returns pointer to student with higest total score
// on tie, returns the one with lowest index
student_t *bestStudent(struct student A[], int n) {
	student_t *max = A + 0;    // A+0 is A is &A[0]
	for (int i = 0; i <= n; i++) {
		if (A[i].totalScore > max->totalScore)
			max = A + i;            // A+i is same as &A[i]
	}
	return max;
}



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 22/07/2022
   ================================================================== */

