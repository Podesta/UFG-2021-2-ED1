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

int binarySearch(int arr[], int beg, int end, int target);

int main(void) {
    int size = 0;
    int target = 0;

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

    printf("\n\nEnter element to be searched: ");
    scanf("%d", &target);

    int found = binarySearch(arr, 0, size - 1, target);
    if (found == -1)
        printf("\n\nElement not present on array.\n");
    else
        printf("\n\nFound element on position %d.\n", found);
}

int binarySearch(int arr[], int beg, int end, int target) {
    int size = end - beg;
    int middle = beg + (size / 2);
    printf("\nbeg: %d // middle: %d // end: %d", beg, middle, end);
    
    if (size < 0)
        return -1;

    if (arr[middle] == target)
        return middle;
    else if (target < arr[middle])
        return binarySearch(arr, beg, middle - 1, target);
    else
        return binarySearch(arr, middle + 1, end, target);
}
