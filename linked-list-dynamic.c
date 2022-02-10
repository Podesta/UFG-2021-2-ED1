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
void printList(struct Header *header);
int printListHelper(struct Node *node);
int nodeHeight(struct Node *node, int *counter);
int nodeDepth(struct Node *node, struct Node *target, int *counter);
bool checkAscending(struct Node *node);
struct Node *searchNode(struct Node *node, int data);
int minNode(struct Node *node, struct Node **currMin);


int main (void) {
    struct Header header = {
        .first = NULL,
        .last = NULL,
        .nNodes = 0,
    };

    while (true) {
        switch (mainMenu()) {
        case '1':
            printf("\nType value to add: ");
            addNode(&header, getData());
            break;
        case '2': {
            int height = 0;
            nodeHeight(header.first, &height);
            printf("\nThe height of the first node is: %d.\n", height);
            break; }
        case '3': {
            int depth = 0;
            nodeDepth(header.first, header.last, &depth);
            printf("\nThe depth of the last node is: %d.\n", depth);
            break; }
        case '4':
            if (checkAscending(header.first))
                printf("\nThe list is in ascending order.\n");
            else
                printf("\nThe list is NOT in ascending order.\n");
            break;
        case '5': {
            printf("\nType value to search: ");
            struct Node *foundNode = searchNode(header.first, getData());
            if (!foundNode) {
                printf("\nData not present in list.\n");
            } else {
                printf("\n%p\n", (void*)foundNode);
            }
            break; }
        case '6': {
            struct Node *currMin = header.first;
            minNode(header.first->next, &currMin);  // Pointer to pointer,
            printf("\n%p\n", (void*)currMin);       // pass address with &
            break; }
        case '9':
            printList(&header);
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
    printf("\n  2 - Height of node");
    printf("\n  3 - Depth of node");
    printf("\n  4 - Check if list is in ascending orger");
    printf("\n  5 - Search in the list");
    printf("\n  6 - Find node with smallest data value");
    printf("\n  9 - Print list");
    printf("\n  0 - Exit\n\n");

    do {
        input = getchar();
        while (getchar() != '\n');
    } while ((input != '0') && (input != '9') && (input != '1') &&
             (input != '2') && (input != '3') && (input != '4') &&
             (input != '5') && (input != '6'));

    return input;
}

int getData(void) {
    int input = 0;
    scanf("%d", &input);
    while (getchar() != '\n');
    return input;
}

void addNode(struct Header *header, int data) {
    struct Node *node = malloc(sizeof(struct Node));

    if (header->first == NULL) {
        node->data = data;
        node->prev = NULL;
        node->next = NULL;
        header->first = node;
        header->last = node;
        ++(header->nNodes);
    } else {
        node->data = data;
        node->prev = header->last;
        node->next = NULL;
        header->last->next = node;
        header->last = node;
        ++(header->nNodes);
    }

    printf("\nNode added with success!\n");
}

void printList(struct Header *header) {
    printf("\nFirst: %p\nLast: %p\nNodes: %d\n", (void*)header->first,
            (void*)header->last, header->nNodes);

    if (header->first != NULL)
        printListHelper(header->first);
}

int printListHelper(struct Node *node) {
    printf("\nData: %5d / Addr: %14p / Prev: %14p / Next: %14p", node->data,
            (void*)node, (void*)node->prev, (void*)node->next);

    if (node->next != NULL) {
        return printListHelper(node->next);
    }

    return 0;
}

int nodeHeight(struct Node *node, int *counter) {
    if (node->next != NULL) {
        ++(*counter);
        return nodeHeight(node->next, counter);
    }

    return 0;
}

int nodeDepth(struct Node *node, struct Node *target, int *counter) {
    if (node == target) {
        return 0;
    } else {
        ++(*counter);
        return nodeDepth(node->next, target, counter);
    }
}

bool checkAscending(struct Node *node) {
    if (node->next == NULL)
        return true;
    else if (node->data > node->next->data)
        return false;
    else
        return checkAscending(node->next);
}

struct Node *searchNode(struct Node *node, int data) {
    if (node->data == data)
        return node;
    else if (node->next != NULL)
        return searchNode(node->next, data);
    else
        return NULL;
}

// I want to change the actual pointer address, so I use pointer to pointer,
// and when calling the function pass the address of the pointer with &.
// The parenthesis when getting the data from pointer to pointer are necessary!!
int minNode(struct Node *node, struct Node **currMin) {
    if (node->data < (*currMin)->data)
        *currMin = node;
    if (node->next != NULL)
        return minNode(node->next, currMin);

    return 0;
}
