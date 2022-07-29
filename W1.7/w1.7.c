/* Skeleton for W1.7, comp20003 workshop Week 1 */

// Using malloc to allocate memory for an array
// Takes a number of words and stores these in the array

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv){
    int numStrings;
    int nextStringLength;
    int i, j;
    char **strings;
    
    /* Read number of strings to store. */
    scanf("%d ", &numStrings);

    /* Allocate space for the array of strings. */
    strings = (char **) malloc(sizeof(char*) * numStrings);

    /* For each string, get its length, allocate space for it
        and read all the characters into the string.
        Note: Remember, these are standard strings. */
    for (j = 0; j < numStrings; j++) {
        scanf("%d ", &nextStringLength);
        strings[j] = (char *) malloc(sizeof(char) * (nextStringLength + 1));
        scanf("%s ", strings[j]);
    }    
    
    /* The below prints all words in the array with spaces between them. */
    if(numStrings > 0){
        printf("%s",strings[0]);
    }
    
    for(i = 1; i < numStrings; i++){
        printf(" %s",strings[i]);
    }
    printf("\n");

    for (j = 0; j < numStrings; j++) {
        free(strings[j]);
    }
    free(strings);
    
    return 0;
}

/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 01/07/2022
   ================================================================== */


