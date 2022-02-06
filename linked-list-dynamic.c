/*******************************************************************************
 * File name     : linked-list-dynamic.c
 * Author        : Podesta
 * Date          : February 2022
 * Version       : 1.0
 * Dependencies  : Standard C libraries
 * Description   : Program implementing a dynamic linked list and functions to
 *                 calculate its height, depth, check if it is ordered, find
 *                 algorithm, etc. Exercise for ED1 class at UFG.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Header {
    struct Node *first;
    struct Node *last;
    int nNodes;
};


int mainMenu(void);
int getData(void);
void addNode(struct Header *header, int data);


int main (void) {
    struct Header header = {
        .first = NULL,
        .last = NULL,
        .nNodes = 0,
    };

    while (true) {
        switch (mainMenu()) {
        case '1':
            addNode(&header, getData());
            break;
        case '0':
            return 0;
        }
    }

    return -1;
}

int mainMenu(void) {
    int input;

    printf("\n############### Dynamic Linked List ##############\n");
    printf("\n  1 - Add element into the list");
    printf("\n  9 - Print list");
    printf("\n  0 - Exit\n\n");

    do {
        input = getchar();
        while (getchar() != '\n');
    } while ((input != '0') && (input != '1'));

    return input;
}

int getData(void) {
    int input = 0;
    printf("\nType value to add: ");
    scanf("%d", &input);
    while (getchar() != '\n');
    return input;
}

void addNode(struct Header *header, int data) {
    struct Node *node = malloc(sizeof(struct Node));

    if (header -> first == NULL) {
        node -> data = data;
        node -> prev = NULL;
        node -> next = NULL;
        header -> first = node;
        header -> last = node;
        ++(header -> nNodes);
    } else {
        node -> data = data;
        node -> prev = header -> last;
        node -> next = NULL;
        header -> last = node;
        ++(header -> nNodes);
    }

    printf("\nfirst: %p\nlast: %p\ncounter: %d\ndata: %d\n", (void*)header -> first, (void*)header -> last, header -> nNodes, node -> data);
    printf("\nNode added with success!\n");
}
