/* Skeleton for W4.7, comp20003 workshop Week 4 */

/* 
   stack.[c,h], postfix.c: demonstrating the use of stack
                           in evaluating postfix expression 
                           (reverse Polish notation)
   CONCEPTS: Postfix expression is an (here, arithmetic) expression
             where operators follow operands, for example:
               3 5 +       means 3 + 5
               2 3 5 + *   means 2 * ( 3 + 5 )
             Here, we use stack to evaluate the expression, for example,
             the second expression is evaluated as:
				read 2
				push 2
				read 3
				push 3
				read 5
				push 5
				read +  (which is an operator requiring 2 operands)
				pop (=5)   
				pop (=3)
				push 3*5 
				read *  (which is an operator requiring 2 operands)
                pop (=15)
				pop (=2)
				push 2*15
                as input finishes, pop (=30) gives the final value
	LIMITATIONS IN THIS PACKAGE:
	   + operands are unsigned integers,
	   + operators can only be BINARY +, -, *, /
	   + only spaces are used to separate the elements in expressions   
 
*/

#define ARRAY_STACK


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
 
#include "stack.h"
 
#define MAX_STRLEN 255   /* max len of expression */

int main(int argc, char *argv[]) {
	char s[MAX_STRLEN + 1];
	char *p;
	int a, b, c;

	while (fgets(s, MAX_STRLEN, stdin)) {   // read new expression to s
		printf("Expression: %s ", s);
		stackADT_t *st = stackCreate();
		int error = 0;
		int empty = 1;
		for (p = s; *p; p++) {
			if (!isspace(*p)) empty = 0;
			if (isdigit(*p)) {              // gets a number
				for (a = 0; *p && isdigit(*p); p++) a = a * 10 + (*p - '0');
				push(st, a);
			} 
			if (isspace(*p)) continue;
			/* now, *p must be a binary operator (a limit of this prog) */
			if (stackCount(st) < 2) { // should have at least 2 operands      
				printf("\tERROR: Too few operands at the start of or in expression\n");
				error= 1;
				break;
			}
			a = pop(st);    // now takes 2 operands & perform calculation
			b = pop(st);
			switch (*p) {
				case '+': c = a + b; break;
				case '-': c = a - b; break;
				case '*': c = a * b; break;
				case '/': c = a / b; break;
				default:
					printf("\tERROR: Unrecognized operator in expression\n");
					error = 1;
					break;
			}
			push(st, c);
		}

		if (empty) {
			printf("\tThe expression is empty\n");
		} else if (!error) {
			if (stackCount(st) != 1) {
				printf("\tERROR: Wrong balance between operators and operands in expression\n");
			} else {
				printf("\tValue = %d\n", pop(st));
			}
		}
		printf("\n");
		stackFree(st);
	}
} 



/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 15/07/2022
   ================================================================== */

