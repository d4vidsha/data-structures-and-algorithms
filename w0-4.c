/* Skeleton for W0.4/E0.12, comp20003 workshop Week 0 */

// string processing: array and pointer notations

/* Write a program that
- Reads a string of at most 79 characters, supposing that a NEWLINE character 
  specifies the end of the input string.
- Has a function which is used for getting the reversed string of the input string.
  For example, if the input string is "ABCD", the reversed string is "DCBA". 
  You should use the array notation for this function.
- Has a function which is used for getting a new string that contains and only 
  contains all alphabetic characters of the input string, in the order of
  appearance. For example, if the input string is "A1 bX", the new string 
  is "AbX". You should use the pointer notation for this function. You might
  find that the library function isalpha is helpful. 
- Finally, prints out the 3 strings, each on its own line, in the above order.
*/

#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 79



/* =====================================================================
   This task is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 15/06/2022
   ================================================================== */
