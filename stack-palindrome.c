/*******************************************************************************
 * File name     : stack-palindrome.c
 * Author        : Podesta
 * Date          : March 2022
 * Version       : 1.0
 * Dependencies  : Standard C libraries
 * Description   : Implement a program to check if a given word is a palindrome
 *                 using a stack (LIFO) data structure. It should not ignore
 *                 empty spaces or special characters.
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static const int LIMIT = 2048;

char pop(char array[]);
bool palindrome(char array1[], char array2[]);

int main(void) {
    char arr[LIMIT];
    char arr2[LIMIT];
    size_t length = 0;

    printf("Enter word or sentence to check if is a palindrome: ");
    fgets(arr, LIMIT, stdin);
    length = strlen(arr);

    if (arr[length-1] == '\n') {
        arr[length-1] = '\0';
        --length;
    } else {
        while (getchar() != '\n');
    }

    strcpy(arr2, arr);
    
    if (palindrome(arr, arr2))
        printf("The given sentence is a palindrome.\n");
    else
        printf("The given sentence is not a palindrome.\n");

    return 0;
}

char pop(char array[]) {
    size_t length = strlen(array);
    char tmp = array[length-1];
    array[length-1] = '\0';
    return tmp;
}

bool palindrome(char array1[], char array2[]) {
    for (size_t i = 0; i < strlen(array1); ++i) {
        if (array1[i] != pop(array2))
            return false;
    }
    return true;
}
