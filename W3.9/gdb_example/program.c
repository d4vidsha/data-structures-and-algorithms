// Program to compute and print out n!

#include <stdio.h>
#include <assert.h>

#define MAX_N 14

int factorial(int n);

int main(int argc, char *argv[]) {
    int n;
    printf("Computing n!. Enter value for n: ");
    assert(scanf("%d", &n) == 1);
    printf("n = %d, n! = %d\n", n, factorial(n));

    return 0;
}

// not an example of good functions!
// the choice of parameter name is really bad
int factorial(int j) {
    int fact = 1;
    int i;
    for (i = 1; i <= j; j++) {
        fact *= i++;
    }
    return fact;
}
