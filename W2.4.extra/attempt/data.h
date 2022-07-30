/* Solution for W2.4, comp20003 workshop Week 2 */

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

// data type definitions
typedef struct student student_t;

// function definition
student_t *readStudent();
void printStudent(student_t *s);

#endif



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 05/07/2022
   ================================================================== */
