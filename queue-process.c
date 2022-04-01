/*******************************************************************************
 * File name     : queue-process.c
 * Author        : Podesta
 * Date          : March 2022
 * Version       : 1.0
 * Dependencies  : Standard C libraries
 * Description   : Implement a dynamic queue that simulates the process and
 *                 time sharing of a CPU, with id, name, priority and wait. It
 *                 should be able to add new processes into the queue, terminate
 *                 the process with longest wait time, execute a process and
 *                 print all processes in the queue.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process {
    size_t id;
    char *name;
    size_t priority;
    size_t wait;
    struct Process *next;
};

int mainMenu(void);
struct Process *initializeQueue(void);
struct Process *getData(void);
void pushProcess(struct Process *header);
struct Process *popProcess(struct Process *header);
struct Process *killByWait(struct Process *header);
void killNode(struct Process *header, struct Process *toKill);
void printProcess(struct Process *node);
void printQueue(struct Process *header);

int main(void) {
    struct Process *header = NULL;

    while (true) {
        switch(mainMenu()) {
        case '1':
            header = initializeQueue();
            break;
        case '2':
            if (!header) {
                printf("\nQueue not yet initialized!\n");
            } else {
                pushProcess(header);
                printf("\nNode successfully added to the queue!\n");
            }
            break;
        case '3':
            if (!header) {
                printf("\nQueue not yet initialized!\n");
            } else if (!header->next) {
                printf("\nQueue is empty!\n");
            } else {
                struct Process *popped = popProcess(header);
                printf("\nProcess '%s' with id %zu finished execution!\n",
                        popped->name, popped->id);
                free(popped->name);
                free(popped);
            }
            break;
        case '4':
            if (!header) {
                printf("\nQueue not yet initialized!\n");
            } else if (!header->next) {
                printf("\nQueue is empty!\n");
            } else {
                struct Process *popped = killByWait(header);
                printf("\nProcess '%s' with id %zu and wait time %zu killed!\n",
                        popped->name, popped->id, popped->wait);
                killNode(header, popped);
            }
            break;
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

    printf("\n###################### Process Queue ######################\n");
    printf("\n 1 - Initialize Process Queue");
    printf("\n 2 - Add process");
    printf("\n 3 - Execute first process in queue");
    printf("\n 4 - Kill process with longest wait time");
    printf("\n 5 - Print all nodes");
    printf("\n 0 - Exit\n\n");

    do {
        input = getchar();
        while (getchar() != '\n');
    } while ((input != '0') && (input != '1') && (input != '2') &&
             (input != '3') && (input != '4') && (input != '5'));

    return input;
}

struct Process *initializeQueue(void) {
    struct Process *queue = malloc(sizeof(struct Process));
    queue->id = 0;
    queue->name = NULL;
    queue->priority = 0;
    queue->next = NULL;

    return queue;
}

struct Process *getData(void) {
    struct Process *newProcess = malloc(sizeof(struct Process));
    char *name = NULL;
    size_t id = 0;
    size_t priority = 0;
    size_t len = 0;
    size_t wait = 0;

    printf("\nEnter id: ");
    scanf("%zu", &id);
    while (getchar() != '\n');

    printf("Enter process name: ");
    long size = getline(&name, &len, stdin);
    name[size - 1] = '\0';

    printf("Enter process priority: ");
    scanf("%zu", &priority);
    while (getchar() != '\n');

    printf("Enter wait time: ");
    scanf("%zu", &wait);
    while (getchar() != '\n');

    newProcess->next = NULL;
    newProcess->id = id;
    newProcess->name = name;
    newProcess->priority = priority;
    newProcess->wait = wait;

    return newProcess;
}

void pushProcess(struct Process *header) {
    while (header->next != NULL) {
        header = header->next;
    }

    struct Process *newProcess = getData();
    header->next = newProcess;
}

struct Process *popProcess(struct Process *header) {
    if (header->next) {
        struct Process *popped = header->next;
        header->next = header->next->next;
        return popped;
    }
    return NULL;
}

void printProcess(struct Process *process) {
    printf("ID: %zu\nName: %s\nPrio: %zu\nWait: %zu\nAddr: %p\nNext: %p\n",
            process->id, process->name, process->priority, process->wait, 
            (void*)process, (void*)process->next);
    printf("--------------------\n");
}

void printQueue(struct Process *header) {
    printf("\n");
    while (header->next) {
        printProcess(header->next);
        header = header->next;
    }
}

struct Process *killByWait(struct Process *header) {
    struct Process *toKill = header->next;
    size_t minWait = header->next->wait;

    while (header->next != NULL) {
        header = header->next;
        if (header->wait > minWait) {
            minWait = header->wait;
            toKill = header;
        }
    }

    return toKill;
}

void killNode(struct Process *header, struct Process *toKill) {
    while (header != NULL && header->next != NULL) {
        if (header->next == toKill) {
            header->next = toKill->next;
        }
        header = header->next;
    }
    free(toKill);
}
