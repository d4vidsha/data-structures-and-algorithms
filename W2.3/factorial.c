// Code to compute n!
#include <assert.h>
#include "factorial.h"

int factorial(int n) {
    assert(n >= 0 && n <= MAX_N && "n must be between 0 and 14"); // won't work with large n 
    int fact = 1;
    while (n > 1) fact *= n--;
    return fact;
}
