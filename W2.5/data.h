/* Solution for W2.5, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  data.h :  
         = the interface of module data of the project
----------------------------------------------------------------*/

#ifndef _DATA_H_
#define _DATA_H_

// constant defnitions
#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 512

// data definitions
struct student {
	int id;
	char *name;     // to facilitate strings with variable length
	double score1;
	double score2;
	double totalScore;
};
typedef struct student student_t;

// function definition

// reads a student from file "f" to build a student_t data
// returns the pointer, or NULL if reading is unsuccessful
student_t *readStudent(FILE *f);

// prints a student record *s to file "f"
void printStudent(FILE *f, student_t *s);

#endif



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 06/07/2022
   ================================================================== */
