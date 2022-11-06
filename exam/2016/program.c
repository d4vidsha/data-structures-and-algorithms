#include <stdlib.h>
#include <stdio.h>

int is_prime(int num);
int max_sum(int *vector, int len);

int main(int argc, char* argv[]) {

    int num = 10;

    if (is_prime(num)) {
        printf("%d is prime\n", num);
    } else {
        printf("%d is not prime\n", num);
    }

    return 0;
}

int is_prime(int num) {
    int flag = 1;

    // 0 and 1 are not primes
    if (num == 0 || num == 1) {
        flag = 0;
        return flag;
    }

    // for every number between 0 and `num`, determine if the number is a
    // factor of any of it's smaller numbers
    for (int i = 2; i < num / 2; i++) {
        if (num % i == 0) {
            flag = 0;
            break;
        }
    }

    return flag;
}

int is_prime(int num) {
    int i;
    for (i = 2; i < num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int is_prime(int num) {

    // take absolute value of number
    if (num < 0) {
        num = -num;
    }

    // only check up to the square root of the number, as any other values
    // beyond that will be a factor of a smaller number
    for (int i = 2; i < pow(num, 0.5); i++) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}

int max_sum(int *vector, int len) {
    int max = 0;


}