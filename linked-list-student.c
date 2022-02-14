/*******************************************************************************
 * File name     : linked-list-student.c
 * Author        : Podesta
 * Date          : February 2022
 * Version       : 1.0
 * Dependencies  : Standard C libraries
 * Description   : Program to implement a student attendance list. The list
 *                 should contain student id number as an int, and the student
 *                 name. It must have functions to insert students, search,
 *                 both by id number and name, and list all the students.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// This time around we will implement it without a specific header. Instead,
// we will use the first node to act as header, storing no data, except the
// location of the first node in the list;

struct Node {
    int idNumber;
    char *name;
    struct Node *next;
    struct Node *prev;
};

int mainMenu(void);
void addNonde(struct Node first, int idNumber, char *name);

int main(void) {

    while (true) {
        switch(mainMenu()) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '0':
                return 0;
        }
    }

    return 1;
}

int mainMenu(void) {
    int input;

    printf("\n#################### Student Attendance ####################\n");
    printf("\n 1 - Add student");
    printf("\n 2 - Search student by id");
    printf("\n 3 - Search student by position in the list");
    printf("\n 4 - List all students");
    printf("\n 0 - Exit\n\n");

    do {
        input = getchar();
        while (getchar() != '\n');
    } while ((input != '0') && (input != '1') && (input != '2') &&
             (input != '3') && (input != '4'));

    return input;
}
