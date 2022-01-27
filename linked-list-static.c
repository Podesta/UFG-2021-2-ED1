/*******************************************************************************
 *
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

int mainMenu(void);
struct Node *initializeList(size_t size);
void printList(struct Node *list);

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
                break;
            case '3':
                break;
            case '4':
                if (list) {
                    printList(list);
                } else {
                    printf("Lista nao inicializada!\n");
                }
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
        printf("  - Posicao: %02ld,  Valor: %03d,  Proximo: %02ld\n",
                i, list[i].data, list[i].next);
    }
}
