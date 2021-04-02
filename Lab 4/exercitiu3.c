#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    double data;
    struct node *prev;
    struct node *next;
} node_t;

typedef double (*node_func_t)(node_t const* node);

void apply(node_t *begin, node_t *end, node_func_t func) {
    if (begin == NULL) return;
    while (begin->next != NULL) {
        begin->data = func(begin);
        begin = begin->next;
    }
}

int main(int argc, char **argv) {

}