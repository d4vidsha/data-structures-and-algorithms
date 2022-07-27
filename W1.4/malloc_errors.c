// Try these out with Valgrind
// Compile with
//   gcc -g -Wall malloc_errors.c -o malloc_errors
//
// Run in Valgrind with
//   valgrind --tool=memcheck ./malloc_errors
//

#include <stdio.h>
// Include the header we need for malloc.
#include <stdlib.h>
// malloc will return NULL if it fails, asserts are a quick way to check success.
#include <assert.h>

#define NUMBEROFINTS 2

int main(int argc, char **argv){
    // We declare space to store a pointer of type int.
    // The value NULL is just an alias for 0 (of pointer type).
    int *values = NULL;

    // Here we allocate space for two integers. The result is a generic pointer,
    // so we also set the type to a pointer to integers.
    values = (int *) malloc(sizeof(int) * NUMBEROFINTS);
    assert(values);

    // Set each of the integers.
    values[0] = 10;
    values[1] = 1;

    // Print the values out.
    printf("%d\n", values[0]);
    printf("%d\n", values[1]);

    // free the malloced memory.
    free(values);

    return 0;
}