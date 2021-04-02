#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void reverse(node_t **node) {
    node_t *n1 = *node;
    node_t *n2, *n3;
    if (n1 != NULL && n1->next != NULL) {
        n2 = n1->next;
    } else {
        return;
    }
    n3 = n2->next;
    n1->next = NULL;
    while (n3 != NULL) {
        n2->next = n1;
        n1 = n2;
        n2 = n3;
        n3 = n3->next;
    }
    n2->next = n1;
    *node = n2;
}
