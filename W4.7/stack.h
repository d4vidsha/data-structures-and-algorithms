/* Skeleton for W4.7, comp20003 workshop Week 4 */

/*-------------------------------------------------------------- 
..Project: postfix
  stack.[c,h] :  module stack of the project
----------------------------------------------------------------*/
#ifndef _STACK_H_
#define _STACK_H_

#include "list.h"

// Note: We want to use data type "stack_t" for our stack
// But the name "stack_t" is already employed by the system
// So here we use "stackADT_t" instead

// FILL IN: define the data type stackADT_t here: ONE simple line


// the rest of this file should not be changed
stackADT_t *stackCreate(); 
void push(stackADT_t *s, int x); 
int pop(stackADT_t *s); 
void stackFree(stackADT_t *s);
int stackCount(stackADT_t *s);

#endif    
			 


/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 15/07/2022
   ================================================================== */

