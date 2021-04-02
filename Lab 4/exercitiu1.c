#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    double data;
    struct node *prev;
    struct node *next;
} node_t;

void push_after(node_t *current, node_t *new_node) {
    new_node->next = current->next;
    current->next = new_node;
    new_node->prev = current;
}

void push_front(node_t **head, node_t *new_node) {
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    new_node->next = *head;
    new_node->prev = NULL;
    (*head)->prev = new_node;
    *head = new_node;
}

void push_back(node_t **head, node_t *new_node) {
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    node_t *parcurs = *head;
    while (parcurs->next != NULL) {
        parcurs = parcurs->next;
    }
    parcurs->next = new_node;
    new_node->next = NULL;
    new_node->prev = parcurs;
}

int main(int argc, char **argv) {
    node_t * head = (node_t *) malloc(sizeof(node_t));
    head->data = 2.3;
    head->prev = NULL;
    head->next = NULL;
    node_t * new = (node_t *) malloc(sizeof(node_t));
    new->data = 5.4;
    new->prev = NULL;
    new->next = NULL;
    push_front(&head, new);
    new = (node_t *) malloc(sizeof(node_t));
    new->data = 2.4;
    new->prev = NULL;
    new->next = NULL;
    push_back(&head, new);
    node_t *parcurs = head;
    while (parcurs != NULL) {
        printf("%lf\n", parcurs->data);
        parcurs = parcurs->next;
    }
    return 0;
}