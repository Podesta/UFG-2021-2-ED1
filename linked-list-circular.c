/*******************************************************************************
 * File name     : linked-list-circular.c
 * Author        : Podesta
 * Date          : March 2022
 * Version       : 1.0
 * Dependencies  : Standard C libraries
 * Description   : Implement a program to perform CRUD operations on a dynamic,
 *                 circular and doubly linked list. It's data should be an int,
 *                 and search operations should be done based on said int.
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
};

int mainMenu(void);
void createNode(struct Header *header);
struct Node *findNode(struct Header *header, struct Node *node, int target);
void printSingleNode(struct Node *node);
void updateNode(struct Node *node);
void deleteNode(struct Header *header, struct Node *node);
int printAllNodes(struct Header *header, struct Node *node);

int main(void) {
    struct Header header = {
        .first = NULL,
        .last = NULL,
    };

    while (true) {
        switch (mainMenu()) {
        case'1':
            createNode(&header);
            break;
        case '2': {
            int target;
            printf("Enter data of node to be printed: ");
            scanf("%d", &target);
            while (getchar() != '\n');
            struct Node *found = findNode(&header, header.first, target);
            if (found)
                printSingleNode(found);
            else
                printf("No node with provided data present on list.\n");
            break; }
        case '3': {
            int target;
            printf("Enter data of node to be updated: ");
            scanf("%d", &target);
            while (getchar() != '\n');
            struct Node *found = findNode(&header, header.first, target);
            if (found)
                updateNode(found);
            else
                printf("No node with provided data present on list.\n");
            break; }
        case '4': {
            int target;
            printf("Enter data of node to be deleted: ");
            scanf("%d", &target);
            while (getchar() != '\n');
            struct Node *found = findNode(&header, header.first, target);
            if (found)
                deleteNode(&header, found);
            else
                printf("No node with provided data present on list.\n");
            break; }
        case '9':
            if (header.first)
                printAllNodes(&header, header.first);
            break;
        case '0':
            return 0;
            break;
        }
    }

    return 1;
}

int mainMenu(void) {
    int input;

    printf("\n############## Dynamic Circular List #############\n");
    printf("\n  1 - Create element into the list");
    printf("\n  2 - Read/search element in the list");
    printf("\n  3 - Update element from list");
    printf("\n  4 - Delete element from list");
    printf("\n  9 - Print list");
    printf("\n  0 - Exit\n\n");

    do {
        input = getchar();
        while (getchar() != '\n');
    } while ((input != '0') && (input != '9') && (input != '1') &&
             (input != '2') && (input != '2') && (input != '3') &&
             (input != '4'));

    return input;
}

void createNode(struct Header *header) {
    struct Node *node = malloc(sizeof(struct Node));
    int data;

    printf("\nEnter data to be added: ");
    scanf("%d", &data);
    while (getchar() != '\n');

    if (header -> first == NULL) {
        node->data = data;
        node->prev = node;
        node->next = node;
        header->first = node;
        header->last = node;
    } else {
        node->data = data;
        node->prev = header->last;
        node->next = header->first;
        header->last->next = node;
        header->first->prev = node;
        header->last = node;
    }

    printf("\nNode created with success!\n");
}

struct Node *findNode(struct Header *header, struct Node *node, int target) {
    if (node == NULL)
        return NULL;
    if (node->data == target)
        return node;
    else if (header->last != node)
        return findNode(header, node->next, target);
    else
        return NULL;
}

void printSingleNode(struct Node *node) {
    printf("Data: %4d / Addr: %14p / Prev: %14p / Next %14p\n", node->data,
            (void*)node, (void*)node->prev, (void*)node->next);
}

void updateNode(struct Node *node) {
    int newData;
    printf("Enter the new data for the node: ");
    scanf("%d", &newData);
    while (getchar() != '\n');

    node->data = newData;
    printf("Data of node with address %p successfully updated to %d.\n",
            (void*)node, node->data);
}

void deleteNode(struct Header *header, struct Node *node) {
    if (header->first == node && header->last == node) {
        header->first = NULL;
        header->last = NULL;
        return;
    }

    if (header->first == node)
        header->first = node->next;
    if (header->last == node)
        header->last = node->prev;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    printf("Node with address %p successfully removed\n", (void*)node);
    free(node);
}

int printAllNodes(struct Header *header, struct Node *node) {
    printSingleNode(node);

    if (header->last == node)
        return 0;
    else
        return printAllNodes(header, node->next);
}
