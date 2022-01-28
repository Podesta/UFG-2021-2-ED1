/*******************************************************************************
 * File name     : linked-list-static.c
 * Author        : Podesta
 * Date          : January 2022
 * Version       : 1.0
 * Dependencies  : Standard C libraries
 * Description   : Program implementing the insertion, removal and print of
 *                 data in a static linked list. Exercise for ED1 class at UFG.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int mainMenu(void);
struct Node *initializeList(size_t size);
void printList(struct Node *list);
void addNode(struct Node *list);

const size_t SIZE = 10;

struct Node {
    bool free;
    int data;
    size_t next;
};

int main(void) {
    struct Node *list;

    while (true) {
        switch (mainMenu()) {
        case '1':
            if (list) {
                //printf("lista: %p", (void *)list);
                free(list);
            }
            list = initializeList(SIZE);
            break;
        case '2':
            if (list)
                addNode(list);
            else
                printf("Lista nao inicializada!\n");
            break;
        case '3':
            break;
        case '4':
            if (list)
                printList(list);
            else
                printf("Lista nao inicializada!\n");
            break;
        case '9':
            return 0;
            break;
        }
    }

    return 0;
}

int mainMenu(void) {
    int input;

    printf("\n1 - Inicializar a lista estática"
           "\n2 - Incluir elementos na lista estática"
           "\n3 - Excluir elementos da lista estática"
           "\n4 - Exibir todos os elementos da lista estática"
           "\n9 - Finalizar\n\n");

    do {
        input = getchar();
        while (getchar() != '\n');
    } while ((input != '1') && (input != '2') && (input != '3') &&
             (input != '4') && (input != '9'));

    return input;
}


struct Node *initializeList(size_t size) {
    struct Node *list = malloc(sizeof(struct Node) * size);

    for (size_t i = 0; i < size; ++i) {
        list[i].data = 0;
        list[i].next = 0;
        list[i].free = true;
    }

    printf("Lista inicializada com sucesso!\n");

    return list;
}


void printList(struct Node *list) {
    for (size_t i = 0; i < SIZE; ++i) {
        printf("  - Posicao: %02zu,  Valor: %03d,  Proximo: %02zu\n",
                i, list[i].data, list[i].next);
    }
}


void addNode(struct Node *list) {
    int data;           // User input
    size_t position;    // User input
    size_t next;        // Check next non free element on list
    size_t prev;        // Check previous non free element on list
    bool checkNext = false;
    bool checkPrev = false;

    printf("Informe a posicao para incluir o elemento (0 a %zu): ", SIZE - 1);
    scanf("%zu", &position);
    printf("Informe o valor do elemento: ");
    scanf("%d", &data);
    while (getchar() != '\n');

    // Get next - This and previous could possibly be split into own function
    for (size_t i = position + 1; i < SIZE; ++i) {
        if (!list[i].free && !checkNext) {  // Check next on loop check.
            next = i;                       // could be swapped with break;
            checkNext = true;
        }
    }

    // Get previous
    // size_t can not be negative. So instead of checking when it reaches
    // a value smaller than 0, we check if the position is smaller than the
    // maximum allowed value for size_t minus 1. When it woudl reach -1 it
    // flips and reaches the maximum value instead;
    for (size_t i = position - 1; i < SIZE_MAX; --i) {
        if (!list[i].free && !checkPrev) {
            prev = i;
            checkPrev = true;
        }
    }

    list[position].data = data;
    list[position].free = false;
    if (checkNext)
        list[position].next = next;
    if (checkPrev)
        list[prev].next = position;

    printf("Elemento adicionado na posicao %zu com sucesso!\n", position);
}
