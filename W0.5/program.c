/* Skeleton for W0.5/E0.13, comp20003 workshop Week 0 */

// Arrays of strings, Anagrams

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

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
int remove_char(char c, char *s);
int in_array(int srch, int *A, int bud);

int main(int argc, char *argv[]) {
    char ss[MAX_STRS][MAX_STR_LEN + 1];
    int n = read_strings(ss);

    // fss will contain the filtered set of strings in a normalised format
    // that only contains alphanumerics and are all lowercases (this allows
    // for the matching to be case insensitive).
    char fss[n][MAX_STR_LEN + 1];
    for (int i = 0; i < n; i++) {
        filter_to_alnums(ss[i], fss[i]);
    }

    // now we compare all strings to each other
    char anagrams[n][n][MAX_STR_LEN + 1];
    int set = 0;
    int counts[n];
    int processed[n];
    int processed_buddy = 0;
    for (int i = 0; i < n; i++) {
        if (in_array(i, processed, processed_buddy)) {
            continue;
        }
        int count = 0;
        for (int j = i + 1; j < n; j++) {
            if (is_anagram(fss[i], fss[j]) 
                && *fss[i] != '\0' 
                && *fss[j] != '\0') {
                if (count == 0) {
                    strcpy(anagrams[set][count], ss[i]);
                    processed[processed_buddy] = i;
                    processed_buddy++;
                    count++;
                }
                strcpy(anagrams[set][count], ss[j]);
                processed[processed_buddy] = j;
                processed_buddy++;
                count++;
            }
        }
        if (count) {
            strcpy(anagrams[set][count], ss[i]);
            counts[set] = count;
            set++;
        }
    }

    for (int i = 0; i < set; i++) {
        printf("#set %d:\n", i + 1);
        for (int j = 0; j < counts[i]; j++) {
            printf("%s\n", anagrams[i][j]);
        }
    }

    // // now we compare all strings to each other
    // char anagrams[n][n][MAX_STR_LEN + 1];
    // int set = 0;
    // for (int i = 0; i < n; i++) {
    //     for (int j = i + 1; j < n; j++) {
    //         if (is_anagram(fss[i], fss[j])) {
    //             strcpy(anagrams[set][0], ss[i]);
    //             strcpy(anagrams[set][1], ss[j]);
                
    //         }
    //     }
    //     set++;
    // }

    // int n_sets = set;
    // for (int i = 0; i < n_sets; i++) {
    //     printf("#set %d:\n", i + 1);
    //     int len = sizeof(anagrams[i]) / sizeof(n * (MAX_STR_LEN + 1));
    //     printf("size: %d\n", len);
    //     for (int j = 0; j < 2; j++) {
    //         printf("%s\n", anagrams[i][j]);
    //     }
    // }


	return 0;
}

int in_array(int srch, int *A, int bud) {
    for (int i = 0; i < bud; i++) {
        if (srch == A[i]) {
            return TRUE;
        }
    }
    return FALSE;
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
    see inspiration: https://www.tutorialspoint.com/learn_c_by_examples/string_anagram_program_in_c.htm
*/
int is_anagram(char *s1, char *s2) {
    int ns1 = strlen(s1), ns2 = strlen(s2);
    
    // if both strings are of different length, then they are not anagrams
    if (ns1 != ns2) {
        return FALSE;
    }

    // sort strings
    int n = ns1;
    char temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (s1[i] > s1[j]) {
                temp  = s1[i];
                s1[i] = s1[j];
                s1[j] = temp;
            }
            if (s2[i] > s2[j]) {
                temp  = s2[i];
                s2[i] = s2[j];
                s2[j] = temp;
            }
        }
    }

    // check character by character
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return FALSE;
        }
    }

    return TRUE;
}

/* Remove character from a string (array of characters)
*/
int remove_char(char c, char *s) {
    int is_done = FALSE;
    int i, n = strlen(s);
    for (i = 0; i < n; i++) {
        if (c == s[i]) {
            while (s[i] != '\0') {
                s[i - 1] = s[i];
                i++;
            }
            s[i] = '\0';
            is_done = TRUE;
            break;
        }
    }
    return is_done;
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
            *(dest + num_alnums) = tolower(src[i]);
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