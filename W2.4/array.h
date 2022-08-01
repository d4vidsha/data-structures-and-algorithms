/* Skeleton for W2.4, comp20003 workshop Week 2 */

/*-------------------------------------------------------------- 
..Project: qStud
  array.c : 
          = the interface of module array of the project
----------------------------------------------------------------*/

#ifndef _ARRAY_H_
#define _ARRAY_H_

// FILL IN THE CONTENT
void freeMemory(student_t *A[], int n);
size_t bytesUsedByArray(student_t *A[], int n);
int buildStudentArray(student_t *A[]);
void printStudentArray(student_t *A[], int n); 
student_t *bestStudent(student_t *A[], int n);



#endif



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 05/07/2022
   ================================================================== */
