// Try these out with Valgrind
// Compile with
//   gcc -g -Wall debug_me.c -o debug_me
//
// Run in Valgrind with
//   valgrind --tool=memcheck ./debug_me
//
#include <stdio.h>

int main(){
    int i, num, j = 1;
    printf ("Enter the number: ");
    scanf ("%d", &num);

    for (i = 1; i <= num; i++)
        j = j * i;    

    printf("The factorial of %d is %d\n", num, j);
}