#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void push_front(node_t **x, double data) {
    node_t *nod = (node_t *) malloc(sizeof(node_t));
    nod->data = data;
    nod->next = *x;
    *x = nod;
}

void push_back(node_t **x, double data) {
    node_t *nod = (node_t *) malloc(sizeof(node_t));
    nod->data = data;
    nod->next = NULL;
    node_t *current = *x;
    if (current != NULL) {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = nod;
    } else {
        *x = nod;
    }
}
