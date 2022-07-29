/* Skeleton for W1.8, comp20003 workshop Week 1 */

// using "getline" to read each line of the input

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv){
    int lineNumber = 0;
    char *line = NULL;
    size_t lineBufferLength = 0;
    
    // no need for the following two lines as getline() deals with this
    // line = (char *)malloc(lineBufferLength * sizeof(char));
    // assert(line);

    /* Read the line. */
    while(getline(&line, &lineBufferLength, stdin) != -1){
        // process the line
        printf("line %d: %s", lineNumber, line);
        lineNumber++;
        
        /* 
            Empty the stdout buffer, not strictly necessary, 
            but might make it easier to see where something's
            going wrong if it is.
        */
        // fflush(stdout);
    }
    
    printf("Program complete!\n");
    fflush(stdout);

    // free after finished with getline() as it will not free itself. However, 
    // it does free itself in the getline function if it were to reallocate.
    free(line);
    
    return 0;
}

// references used:
// https://c-for-dummies.com/blog/?p=1112
// https://man7.org/linux/man-pages/man3/getline.3.html