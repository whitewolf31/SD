#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------- OPERATION CODE (pt undo) --------------
// b = 0
// dl [line] = 1
// gl [line] = 2
// gc char [line] = 3
// d [chars] = 4
// re old_word new_word = 5
// ra old_word new_word = 6
// dw word = 7
// da word = 8
// no operation (daca doar e text inputat) = 9

typedef struct node {
    unsigned char c;
    short int save;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct queue {
    node_t *front;
    node_t *back;
    size_t size;
} queue_t;

typedef struct stack {
    node_t *front;
    size_t size;
} stack_t;

queue_t * alloc_queue() {
    queue_t * queue = (queue_t *) malloc(sizeof(queue_t));
    queue->size = 0;
    queue->back = NULL;
    queue->front = NULL;
    return queue;
}

stack_t * alloc_stack() {
    stack_t * stack = (stack_t *) malloc(sizeof(stack_t));
    stack->size = 0;
    stack->front = NULL;
    return stack;
}

void add_to_list(node_t **list, node_t * new_list) {
    node_t *looper = *list;
    if (looper == NULL) {
        *list = new_list;
        return;
    };
    while (looper->next != NULL) looper = looper->next;
    new_list->prev = looper;
    looper->next = new_list; 
}

int check_start_command(node_t *list) {
    if (list != NULL && list->c == ':' && list->next != NULL && list->next->c == ':' && list->next->next && list->next->next->c == 'i') return 1;
    return 0;
}

void free_list(node_t **list) {
    while ((*list)->next != NULL) {
        *list = (*list)->next;
        free((*list)->prev);
    }
    free(*list);
}

int main(int argc, char *argv[]) {
    stack_t * undo_stack = alloc_stack();
    stack_t * redo_stack = alloc_stack();
    node_t * text = (node_t *) malloc(sizeof(node_t));
    text = NULL;
    FILE *in, *out;
    in = fopen("/home/laurentiu/Scoala/Structuri de Date/Tema 1/editor.in", "r+");
    out = fopen("/home/laurentiu/Scoala/Structuri de Date/Tema 1/editor.out", "w");
    if (in == NULL || out == NULL) return 1;
    char current;
    int command_mode = 0;
    node_t * current_line = (node_t *) malloc(sizeof(node_t));
    current_line = NULL;
    do {
        node_t *new_char = (node_t *) malloc(sizeof(node_t));
        current = fgetc(in);
        if (feof(in)) break;
        new_char->c = current;
        new_char->next = NULL;
        new_char->prev = NULL;
        add_to_list(&current_line, new_char);
        if (current == '\n') {
            if (check_start_command(current_line)) {
                command_mode = !command_mode;
            } else if(command_mode) {
                int x = 3;
            } else {
                add_to_list(&text, current_line);
            }
            current_line = NULL;
        }
    } while (1);
    while (text != NULL) {
        printf("%c", text->c);
        node_t *aux = text->next;
        free(text);
        text = aux;
    }
    fclose(in);
    fclose(out);
    return 0;
}