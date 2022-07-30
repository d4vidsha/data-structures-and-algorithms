// Program to compute and print out n! and nCk

#include <stdio.h>
#include <assert.h>
#include "combination.h"
#include "factorial.h"

int main(int argc, char *argv[]) {
    int n, k;
    printf("Computing n! and nCk. Enter value for n, k: ");
    assert(scanf("%d%d", &n, &k) == 2 && k <= n && k >= 0);
    printf("n= %d, k= %d, n!= %d, nCk= %d\n", 
            n, k, factorial(n), nCk(n, k));

    return 0;
}

