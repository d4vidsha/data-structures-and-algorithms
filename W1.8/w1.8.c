/* Skeleton for W1.8, comp20003 workshop Week 1 */

// using "getline" to read each line of the input

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv){
    int lineNumber = 0;
    char *line = NULL;
    size_t lineBufferLength = 0;
    
    getline(line, &lineBufferLength, stdin);

    while(/* Still input to get from stdin. */){
        /* Read the line. */

        printf("line %d: %s\n", lineNumber, line);
        
        /* 
            Empty the stdout buffer, not strictly necessary, 
            but might make it easier to see where something's
            going wrong if it is.
        */
        fflush(stdout);
    }
    
    printf("Program complete!\n");
    fflush(stdout);
    
    return 0;
}
