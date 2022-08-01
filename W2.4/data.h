/* Skeleton for W2.4, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  data.h :  
         = the interface of module data of the project
----------------------------------------------------------------*/

#ifndef _DATA_H_
#define _DATA_H_
// FILL IN THE FOLLOWING CONTENT
// Constant definitions
#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 512
#define MAX_STUDENTS 5000

// Data definitions
struct student;
typedef struct student student_t;

// Function prototypes
student_t *readStudent();
void printStudent(student_t *s);

#endif



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 05/07/2022
   ================================================================== */
