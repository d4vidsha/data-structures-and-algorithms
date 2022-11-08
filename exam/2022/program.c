#include <stdio.h>
#include <stdlib.h>

// prototypes
int planets_aligned(int* positions, int num_planets);
void increment_positions(int* positions, int* orbit_times, int num_planets);

/**
 * Main function.
 */
int main(int argc, char* argv[]) {

    // read the number of planets and their orbit time
    int num_planets;
    fscanf(stdin, "%d", &num_planets);

    // allocate memory for the positions and orbit times which are both set 
    // to 0 initially
    int* positions = (int *)calloc(num_planets, sizeof(int));
    int* orbit_times = (int *)calloc(num_planets, sizeof(int));

    // read the positions of the planets
    for (int i = 0; i < num_planets; i++) {
        fscanf(stdin, " %d", &orbit_times[i]);
    }

    // increment to the first position
    increment_positions(positions, orbit_times, num_planets);

    // see how long it takes for the planets to align
    int wait = 1;
    while (!planets_aligned(positions, num_planets)) {
        wait++;

        // increment the positions and go back to start once a full 
        // orbit occurs
        increment_positions(positions, orbit_times, num_planets);
    }
    
    // print number of seconds to wait
    printf("%d\n", wait);

    // free memory
    free(positions);
    free(orbit_times);

}

/**
 * Given an array of planets positions, return 1 if the planets are at 
 * position 0, or return 0 otherwise.
 */
int planets_aligned(int* positions, int num_planets) {

    for (int i = 0; i < num_planets; i++) {
        if (positions[i] != 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * Increment the positions of the planets to the next position, but orbit back
 * to the start once a full orbit is completed.
 */
void increment_positions(int* positions, int* orbit_times, int num_planets) {
    for (int i = 0; i < num_planets; i++) {
        positions[i] = (positions[i] + 1) % orbit_times[i];
    }
}