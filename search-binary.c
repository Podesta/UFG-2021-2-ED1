
/*******************************************************************************
 * File name     : linked-list-dynamic.c
 * Author        : Podesta
 * Date          : March 2022
 * Version       : 1.0
 * Dependencies  : Standard C libraries
 * Description   : Program implementing a binary search on an array that is
 *                 already in ascending order.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int size = 0;

    printf("\nDetermine the size of the array: ");
    scanf("%d", &size);

    int arr[size];

    // Populate array;
    for (int i = 0; i < size; ++i) {
        int digit = rand() % 10 * i;

        while (i > 0 && digit < arr[i - 1])
            digit = rand() % 10 * i;

        arr[i] = digit;
    }

    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);

}
