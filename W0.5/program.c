/* Skeleton for W0.5/E0.13, comp20003 workshop Week 0 */

// Arrays of strings, Anagrams

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STRS 1000
#define MAX_STR_LEN 99

#define NUM_LETTERS 26
#define NUM_DIGITS 10
#define SIZE (NUM_LETTERS + NUM_DIGITS)

#define FALSE 0
#define TRUE 1

int read_strings(char ss[][MAX_STR_LEN + 1]);
int is_anagram(char *s1, char *s2);
int filter_to_alnums(char src[], char *dest);

int main(int argc, char *argv[]) {
    char ss[MAX_STRS][MAX_STR_LEN + 1];
    int n = read_strings(ss);

    // temporarily print to stdout the inputs
    for (int i = 0; i < n; i++) {
        printf("%s\n", ss[i]);
    }




    char alnums_only[MAX_STR_LEN + 1];
    n = filter_to_alnums("d^& 4v/^id(sh&a$", alnums_only);
    printf("Filtered input to length of %d: %s\n", n, alnums_only);





	return 0;
}

int read_strings(char ss[][MAX_STR_LEN + 1]) {
	int n = 0;
	printf("Enter strings (max=%d characters each):\n", MAX_STR_LEN);
	for ( ; n < MAX_STRS && scanf(" %[^\n]", ss[n]) == 1; n++);
	return n;
}


/*  returns 1 if the two strings contain the same letters & digits, 
    possibly in a different order, and 0 otherwise, 
    ignoring whitespace characters, and ignoring case
    in addition, ignoring any non-alphanumeric characters,
*/
int is_anagram(char *s1, char *s2) {
    int condition = TRUE;
   
    // int is1, ns1 = strlen(s1);
    // int is2, ns2 = strlen(s2);

    // char alnums_only[MAX_STR_LEN + 1];




    return condition;
}

/*  Given a string, filter out the characters of that string to only include
    alphanumerical values. Returns the number of alphanumerical values found
    in the string.
*/
int filter_to_alnums(char src[], char *dest) {
    int i, n = strlen(src);
    int num_alnums = 0;
    for (i = 0; i < n; i++) {
        // printf("%c\n", src[i]);
        // printf("isalnum: %d\n", isalnum(src[i]));
        if (isalnum(src[i])) {
            // printf("%c\n", src[i]);
            *(dest + num_alnums) = src[i];
            // dest[num_alnums] = src[i];
            num_alnums++;
        }
    }
    // *(dest + num_alnums) = '\0';
    dest[num_alnums] = '\0';
    return num_alnums;
}


/* =====================================================================
   This skeleton/program is compiled by the comp20003 teaching team,
   the university of Melbourne.
   Last Updated: 23/06/2022
   ================================================================== */