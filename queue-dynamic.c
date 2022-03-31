/*******************************************************************************
 * File name     : queue-dynamic.c
 * Author        : Podesta
 * Date          : March 2022
 * Version       : 1.0
 * Dependencies  : Standard C libraries
 * Description   : Implement a dynamic queue that is able to do the following:
 *                 add a node, initialize an empty queue, push at the end, pop
 *                 from the beginning, search, and print all.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node *next;
};

int mainMenu(void);
struct Node *initializeQueue(void);
struct Node *getData(void);
void pushNode(struct Node *header);
void popNode(struct Node *header);
struct Node *searchByPosition(struct Node *header, int position);
void printNode(struct Node *node);
void printQueue(struct Node *header);

int main(void) {
    struct Node *header = NULL;

    while (true) {
        switch(mainMenu()) {
        case '1':
            header = initializeQueue();
            break;
        case '2':
            if (!header) {
                printf("\nQueue not yet initialized!\n");
            } else {
                pushNode(header);
                printf("\nNode successfully added to the queue!\n");
            }
            break;
        case '3':
            if (!header) {
                printf("\nQueue not yet initialized!\n");
            } else if (!header->next) {
                printf("\nQueue is already empty!\n");
            } else {
                popNode(header);
                printf("\nNode successfully removed from the queue!\n");
            }
            break;
        case '4': {
            int position;
            if (!header) {
                printf("\nQueue not yet initialized!\n");
            } else if (!header->next) {
                printf("\nQueue is empty!\n");
            } else {
                printf("Enter position (0 indexed): ");
                scanf("%d", &position);
                while (getchar() != '\n');

                struct Node *found = searchByPosition(header, position);
                if (found)
                    printNode(found);
                else
                    printf("Node with given index does not exist!\n");
            }
            break; }
        case '5':
            if (!header)
                printf("\nQueue not yet initialized!\n");
            else if (!header->next)
                printf("\nQueue is empty!\n");
            else
                printQueue(header);
            break;
        case '0':
            return 0;
        }
    }
    return 1;
}

int mainMenu(void) {
    int input;

    printf("\n###################### Dynamic Queue ######################\n");
    printf("\n 1 - Initialize queue");
    printf("\n 2 - Add node");
    printf("\n 3 - Remove from queue");
    printf("\n 4 - Search node");
    printf("\n 5 - Print all nodes");
    printf("\n 0 - Exit\n\n");

    do {
        input = getchar();
        while (getchar() != '\n');
    } while ((input != '0') && (input != '1') && (input != '2') &&
             (input != '3') && (input != '4') && (input != '5'));

    return input;
}

struct Node *initializeQueue(void) {
    struct Node *queue = malloc(sizeof(struct Node));
    queue->data = 0;
    queue->next = NULL;

    return queue;
}

struct Node *getData(void) {
    struct Node *newNode = malloc(sizeof(struct Node));
    int data = 0;

    printf("\nEnter data: ");
    scanf("%d", &data);
    while (getchar() != '\n');

    newNode->next = NULL;
    newNode->data = data;

    return newNode;
}

void pushNode(struct Node *header) {
    while (header->next != NULL) {
        header = header->next;
    }

    struct Node *newNode = getData();
    header->next = newNode;
}

void popNode(struct Node *header) {
    if (header->next) {
        struct Node *tmp = header->next;
        header->next = header->next->next;
        free(tmp);
    }
}

void printNode(struct Node *node) {
    printf("Data: %3d // Addr: %p // Next: %p\n",
            node->data, (void*)node, (void*)node->next);
}

void printQueue(struct Node *header) {
    while (header->next) {
        printNode(header->next);
        header = header->next;
    }
}

struct Node *searchByPosition(struct Node *header, int position) {
    if (position < 0)   // No negative positions
        return NULL;

    while (position >= 0 && header->next != NULL) {
        header = header->next;
        --position;
    }

    if (position >= 0)  // Couldn't reach position
        return NULL;
    else
        return header;
}
