/* Skeleton for W0.6/E0.15, comp20003 workshop Week 0 */

// A Touch Of Reality

#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 1000
#define MAX_CITY_NAME_LEN 30
#define MAX_HEADER_LINE_LEN 200

struct city {
    char name[MAX_CITY_NAME_LEN + 1];
    int population;
    int national_population_percent;
}
typedef struct city city_t;

int read_city(city_t *ct);
int build_city_array(city_t A[]);

int main(int argc, char **argv){

    if (argc <= 1) {
        printf("%s\n", "ERROR: No input arguments.");
        return EXIT_FAILURE;
    }
    
    if (argc >= 3) {
        printf("%s\n", "ERROR: Too many input arguments.");
        return EXIT_FAILURE;
    }

    // there can only be 1 input argument from here on
    printf("argv[1]: %s\n", argv[1]);
    city_t cities[MAX_CITIES];
    n = build_city_array[cities];


    return EXIT_SUCCESS;
}

/*  Read a city from stdin to *ct and returns 1 if successful, 0 if not.
*/
int read_city(city_t *ct) {

}

/*  Read data from stdin, builds array of cities, and returns the number of
    cities.
*/
int build_city_array(city_t A[]) {

}