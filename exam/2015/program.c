#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSTRING 256
#define TRUE 1
#define FALSE 0
#define MALLOCERROR 2

/* prototypes */
int checkpalindrome(char *buffer);

/**
 * @brief main(). No inputs. Reads in from stdin, line-by-line, and calls
 * function checkpalindrome. Prints the line of checkpalindrome returns TRUE.
 */
int main(int argc, char **argv) {
    char *buffer;

    if ((buffer = (char *)malloc(MAXSTRING))==NULL) {
        printf("Error: malloc failed");
        exit(MALLOCERROR);
    }

    while ((buffer=fgets(buffer,MAXSTRING,stdin))!=NULL)
        if (checkpalindrome(buffer)) printf("%s", buffer);

    return(TRUE);
}

/**
 * @brief checkpalindrome. Takes a string and returns TRUE if the string is a
 * palindrome, FALSE otherwise. 
 * - Ignores whitespaces, numbers, punctuation, and case if the string is a 
 *   sentence.
 * - Ignores punctuation and case if the string is a word.
 */
int checkpalindrome(char *buffer) {
    int i, j, len, isword, ispalindrome;
    char *word;

    /* check if string is a word or a sentence */
    if (strchr(buffer, ' ') == NULL) isword = TRUE;
    else isword = FALSE;

    /* remove whitespace, numbers, and punctuation */
    len = strlen(buffer);
    if ((word = (char *)malloc(len))==NULL) {
        printf("Error: malloc failed");
        exit(MALLOCERROR);
    }
    for (i=0, j=0; i<len; i++) {
        if (!isword) {
            if (isalpha(buffer[i])) {
                word[j] = tolower(buffer[i]);
                j++;
            }
        } else {
            if (isalpha(buffer[i]) || isdigit(buffer[i])) {
                word[j] = tolower(buffer[i]);
                j++;
            }
        }
    }
    word[j] = '\0';

    /* check if word is a palindrome */
    len = strlen(word);
    ispalindrome = TRUE;
    for (i=0, j=len-1; i<len/2; i++, j--) {
        if (word[i] != word[j]) {
            ispalindrome = FALSE;
            break;
        }
    }

    free(word);
    return(ispalindrome);
}

// /**
//  * @brief Exam solution.
//  */
// int checkpalindrome(char *buffer) {
//     int i, j;

//     // we will use a kind of inverted quicksort partition idea to find values
//     // which should be on both sides
//     i = -1;
//     j = strlen(buffer);

//     while(i < j) {
//         i++;
//         j--;

//         // move over irrelevant characters
//         while(i < j && !isalpha(buffer[i])) {
//             i++;
//         }

//         // move over irrelevant characters
//         while(i < j && !isalpha(buffer[j])) {
//             j--;
//         }

//         // cross over (we know the character at i == j is the same for
//         // buffer[i] and buffer[j])
//         if (i >= j) {
//             // palindrome
//             break;
//         }

//         // only need to compare lowercase letters as case insentitive
//         if (tolower(buffer[i]) != tolower(buffer[j])) {
//             // not a palindrome
//             return 0;
//         }
//     }

//     // palindrome
//     return 1;
// }