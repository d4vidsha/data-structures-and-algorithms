// Code to compute n!
#include <assert.h>
#include "combination.h"

// Returns the number of k-combinations of n
int nCk(int n, int k) {
    assert (n >= 0 && k <= n);
    return factorial(n) / (factorial(k) * factorial(n - k));
}
