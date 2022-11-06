#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int total_dist(int x, int nRel, int* stNum) {
    int total = 0;
    for (int i = 0; i < nRel; i++) {
        total += abs(x - stNum[i]);
    }
    return total;
}

int main(int argc, char* argv[]) {

    int nRel;
    scanf("%d", &nRel);

    // initialise array to store street numbers
    int* stNum = (int *)malloc(sizeof(int) * nRel);
    assert(stNum);

    // populate array with street numbers
    for (int i = 0; i < nRel; i++) {
        stNum[i] = rand() % 100;
    }
    
    // find the minimum distance for each street number
    int min = INFINITY;
    int dist;
    int minStNum;
    for (int i = 0; i < nRel; i++) {
        dist = total_dist(stNum[i], nRel, stNum);
        if (dist < min) {
            minStNum = stNum[i];
            min = dist;
        }
    }

    printf("Street number: %d\nTotal distance: %d\n", minStNum, min);

    free(stNum);
}