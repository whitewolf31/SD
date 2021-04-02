#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void map(node_t *x, node_func_t func) {
    while (x != NULL) {
        x->data = func(x);
        x = x->next;
    }
}

void filter(node_t **x, node_func_t func) {
    node_t *aux = *x;
    while (aux->next != NULL) {
        if (func(aux->next) > 0) {
            aux->next = (aux->next)->next;
        } else {
            aux = aux->next;
        }
    }
    aux = *x;
    while (func(aux) > 0) {
        *x = aux->next;
        aux = *x;
    }
}

double aggregate(node_t *x, node_func_t func) {
    double sum = 0;
    while (x != NULL) {
        sum += func(x);
        x = x->next;
    }
    return sum;
}
