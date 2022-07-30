// factorial.h: Interface of Code to compute n!
#ifndef _FACTORIAL_H_
    // the part between #ifndef and #endif is pasted
    //    to the #include-ing file 
    //    only if the constant _FACTORIAL_H_ is not defined there

// define a constant with name _FACTORIAL_H_ and no value
#define _FACTORIAL_H_

// defintion of constants and data types
#define MAX_N 14

// Example data type - unused in code.
struct factorial;
// Note that this is the implementation of struct factorial
// and would not cause errors if this was only present in factorial.c
struct factorial {
    int n;
};

// Function prototypes
int factorial(int n);

#endif

