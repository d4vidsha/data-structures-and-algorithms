/* Skeleton for W0.6/E0.15, comp20003 workshop Week 0 */

// A Touch Of Reality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR2(x) #x			// see https://stackoverflow.com/a/25410835
#define STR(X) STR2(X)		//

#define TRUE 1
#define FALSE 0

#define MAX_CITIES 1000
#define MAX_CITY_NAME_LEN 30
#define MAX_HEADER_LINE_LEN 200

struct city {
    char name[MAX_CITY_NAME_LEN + 1];
    int population;
    float national_population_percent;
};
typedef struct city city_t;

int read_city(city_t *ct);
int build_city_array(city_t A[]);
void print_city(city_t *ct);
void print_city_array(city_t A[], int n);
void organise_alphabetically(city_t A[], int n);
void highest_population(city_t A[], int n);

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
    int n = build_city_array(cities);

    // organise into alphabetical order
    organise_alphabetically(cities, n);

    // print to stdout list of cities in alphabetical order
    printf("LIST OF CITIES IN ALPHABETICAL ORDER\nCity, Population June 2020, %% of national population June 2019\n");
    print_city_array(cities, n);

    // highest population city
    highest_population(cities, n);

    return EXIT_SUCCESS;
}

/*  Read a city from stdin to *ct and returns `TRUE` if successful, `FALSE` 
    if not.
*/
int read_city(city_t *ct) {
    char name[MAX_CITY_NAME_LEN];
    int pop;
    double npp;

    if (scanf(" %[^,], %d, %lf%%", name, &pop, &npp) == 3) {
        strcpy(ct->name, name);
        ct->population = pop;
        ct->national_population_percent = npp;
        return TRUE;
    }
    return FALSE;
}

/*  Read data from stdin, builds array of cities, and returns the number of
    cities.
*/
int build_city_array(city_t A[]) {
    int n;
    char header[MAX_HEADER_LINE_LEN + 1];

    // gets rid of the header line
    scanf("%" STR(MAX_HEADER_LINE_LEN) "[^\n] ", header);   // see https://stackoverflow.com/a/25410835 
													        // and https://stackoverflow.com/a/40039758
    // alternatively, just use
    // while (getchar() != '\n');

    // reads and stores students in students array
    for (n = 0; n < MAX_CITIES && read_city(&A[n]); n++);

    // reads rest of stdin without doing anything to the provided data
    // as the maximum number of cities have been reached
    if (n == MAX_CITIES) {
        while (getchar() != EOF);
    }

    return n;
}

/* Prints a city record *ct to stdout.
*/
void print_city(city_t *ct) {
    printf("%s, %d, %.2lf%%\n", 
            ct->name, 
            ct->population, 
            ct->national_population_percent);
}

/* Prints the array of cities.
*/
void print_city_array(city_t A[], int n) {
    for (int i = 0; i < n; i++) {
        print_city(&A[i]);
    }
}

/* Organise cities in alphabetical order.
*/
void organise_alphabetically(city_t A[], int n) {
    for (int i = 0; i < n; i++) {
        city_t *ct1 = &A[i];
        char *name1 = ct1->name;
        for (int j = i + 1; j < n; j++) {
            city_t *ct2 = &A[j];
            char *name2 = ct2->name;
            // printf("A[%d]->name: %s\n", i, name1);
            // printf("A[%d]->name: %s\n", i, name2);
            if (strcmp(name1, name2) > 0) {
                city_t temp = *ct1;
                ct1 = ct2;
                ct2 = &temp;
                A[i] = *ct1;
                A[j] = *ct2;
                // printf("A[%d]->name: %s\n", i, ct1->name);
                // printf("A[%d]->name: %s\n", i, ct2->name);
            }
            // printf("\n");
        }
    }
}

/*  Given an array of cities, find the city with the highest population and
    print to stdout.
*/
void highest_population(city_t A[], int n) {
    city_t *max = A + 0;    // A + 0 == A == &A[0]

    for (int i = 0; i < n; i++) {
        if (A[i].population > max->population) {
            max = A + i;
        }
    }
    return max;
}