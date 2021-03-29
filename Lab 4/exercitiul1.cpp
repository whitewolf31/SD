#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void push_after(node_t *current, node_t *new_node) {
    new_node->next = current->next;
    current->next = new_node;
    new_node->prev = current;
}

void push_front(node_t **head, node_t *new_node) {
    new_node->next = *head;
    new_node->prev = NULL;
    (*head)->prev = new_node;
    *head = new_node;
}

void push_back(node_t **head, node_t *new_node) {

}
