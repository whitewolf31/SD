#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    double data;
    struct node *prev;
    struct node *next;
} node_t;

void remove(node_t **node) {
    (*node)->prev->next = (*node)->next;
    (*node)->next->prev = (*node)->prev;
    free(*node);
}

node_t *nth_element(const node_t *head, const size_t nth) {
    int i = 0;
    node_t *parcurs = head;
    while (parcurs->next != NULL) {
        if (i == nth) {
            return parcurs;
        }
        parcurs = parcurs->next;
    }
    return parcurs;
}

int main(int argc, char **argv[]) {

}
