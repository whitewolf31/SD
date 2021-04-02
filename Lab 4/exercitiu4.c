#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    double data;
    struct node *prev;
    struct node *next;
} node_t;

typedef double (*node_func_t)(node_t const* node);

double testFunc(const node_t * node) {
    return node->data;
}

size_t remove_equal_sequence(node_t **begin, node_func_t func) {
    size_t nr_nod_del = 0;
    node_t *parcurs = *begin;
    if (parcurs == NULL) return 0;
    int seq = 1;
    double currentFuncVal = func(parcurs);
    while (parcurs->next != NULL) {
        if (func(parcurs->next) != currentFuncVal) {
            currentFuncVal = func(parcurs->next);
            if (seq >= 3) {
                node_t *current = parcurs->next;
                while (seq > 0) {
                    parcurs = parcurs->prev;
                    free(parcurs->next);
                    seq--;
                    nr_nod_del++;
                }
                if (parcurs == NULL) {
                    current->prev = NULL;
                    *begin = current;
                } else {
                    parcurs->next = current;
                    current->prev = parcurs;
                }
                parcurs = current;
            } else {
                parcurs = parcurs->next;
            }
            seq = 1;
        } else {
            seq++;
            parcurs = parcurs->next;
        }
    };
    if (seq >= 3) {
        while (seq > 0) {
            parcurs = parcurs->prev;
            free(parcurs->next);
            seq--;
            nr_nod_del++;
        }
        if (parcurs == NULL) *begin = NULL;
        else parcurs->next = NULL;
    }
    return nr_nod_del;
}

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
    head->data = 1;
    head->prev = NULL;
    head->next = NULL;
    double v[15] = {2, 3, 3, 3, 7, 7, 6, 5, 5, 5, 5};
    for (int i = 0; i < 11; i++) {
        node_t * new = (node_t *) malloc(sizeof(node_t));
        new->data = v[i];
        new->prev = NULL;
        new->next = NULL;
        push_back(&head, new);
    }
    size_t result = remove_equal_sequence(&head, testFunc);
    printf("%ld\n", result);
    node_t *parcurs = head;
    while (parcurs != NULL) {
        printf("%lf\n", parcurs->data);
        parcurs = parcurs->next;
    }
    return 0;
}