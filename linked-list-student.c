/*******************************************************************************
 * File name     : linked-list-student.c
 * Author        : Podesta
 * Date          : February 2022
 * Version       : 1.0
 * Dependencies  : Standard C libraries
 * Description   : Program to implement a student attendance list. The list
 *                 should contain student id number as an int, and the student
 *                 name. It must have functions to insert students, search,
 *                 by id number and by position, and list all the students.
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
void addNonde(struct Node *first);
int printAll(struct Node *node);
void printSingle(struct Node *node);
struct Node *searchById(struct Node *node, int idNumber);
struct Node *searchByPosition(struct Node *node, int *position);

int main(void) {
    struct Node *first = malloc(sizeof(struct Node));
    first->idNumber = 0;
    first->name = NULL;
    first->next = NULL;
    first->prev = NULL;

    while (true) {
        switch(mainMenu()) {
            case '1':
                addNonde(first);
                break;
            case '2': {
                int id;
                printf("Enter student id to search: ");
                scanf("%d", &id);
                while (getchar() != '\n');
                struct Node *found = searchById(first->next, id);
                if (found)
                    printSingle(found);
                else
                    printf("No student with id #%d on the list.\n", id);
                break; }
            case '3': {
                int pos;
                printf("Enter position to find on the list: ");
                scanf("%d", &pos);
                while (getchar() != '\n');
                struct Node *found = searchByPosition(first->next, &pos);
                if (found)
                    printSingle(found);
                else
                    printf("There are no students at specicied position.\n");
                break; }
            case '4':
                if (first->next)
                    printAll(first->next);
                else
                    printf("There are no students in the list.\n");
                break;
            case '0':
                free(first);
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


void addNonde(struct Node *first) {
    struct Node *node = malloc(sizeof(struct Node));
    int idNumber;
    char *name = NULL;
    size_t len = 0;     // Without a pointer for len, getline fails;

    // Get last node in the list
    while (first->next != NULL)
        first = first->next;

    // Get input
    printf("Enter name of student: ");
    long size = getline(&name, &len, stdin);
    name[size - 1] = '\0';      // Remove newline from name
    do {
        printf("Enter id number of student: ");
        scanf("%d", &idNumber);
        while (getchar() != '\n');  // Clear input buffer
    } while (idNumber <= 0);

    node->idNumber = idNumber;
    node->name = name;
    node->next = NULL;
    node->prev = first;

    first->next = node;
}


int printAll(struct Node *node) {
    printSingle(node);

    if (node->next != NULL)
        return printAll(node->next);

    return 0;
}


void printSingle(struct Node *node) {
    printf("Name: %s\n", node->name);
    printf("Id number: %d\n", node->idNumber);
    printf("Prev: %p  //  Addr: %p  //  Next: %p\n",
            (void*)node->prev, (void*)node, (void*)node->next);
    printf("----------\n");
}


struct Node *searchById(struct Node *node, int idNumber) {
    if (node->idNumber == idNumber)
        return node;
    else if (node->next != NULL)
        return searchById(node->next, idNumber);
    else
        return NULL;
}


struct Node *searchByPosition(struct Node *node, int *position) {
    if (*position == 0) {
        return node;
    } else if (node->next != NULL) {
        --(*position);
        return searchByPosition(node->next, position);
    } else {
        return NULL;
    }
}
