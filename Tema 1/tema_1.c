#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    unsigned char c;
    short int save;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct stack_node {
    node_t *list;
    node_t *back;
    struct stack_node *next;
    node_t *command;
    int prev_line;
    int prev_c;
    int stop;
} stack_node_t;

typedef struct stack {
    stack_node_t *front;
    size_t size;
} stack_t;

typedef struct cursor {
    node_t *first;
    node_t *current_node;
    int line;
    int c;
} cursor_t;

stack_t * alloc_stack() {
    stack_t * stack = (stack_t *) malloc(sizeof(stack_t));
    stack->size = 0;
    stack->front = NULL;
    return stack;
}

void command_decide(stack_t **undo_stack, stack_t **redo_stack, node_t *current_line, cursor_t ** cursor, int redo_stack_call);
void pop_and_undo(stack_t ** undo_stack, stack_t ** redo_stack, cursor_t **cursor);
void pop_and_redo(stack_t ** undo_stack, stack_t ** redo_stack, cursor_t **cursor);

void add_to_stack(stack_t ** stack, stack_node_t *node) {
    if ((*stack)->front == NULL) {
        (*stack)->front = node;
    } else {
        node->next = (*stack)->front;
        (*stack)->front = node;
    }
    (*stack)->size++;
}

void add_to_cursor_list(cursor_t **cursor, node_t * new_list) {
    node_t *looper, *next_node = NULL;
    if ((*cursor)->first == NULL) {
        (*cursor)->first = new_list;
    } else {
        next_node = (*cursor)->current_node->next;
        (*cursor)->current_node->next = new_list;
        new_list->prev = (*cursor)->current_node;
    }
    looper = new_list;
    while (looper != NULL && looper->next != NULL) {
        if (looper->c == '\n') {
            ((*cursor)->line)++;
            (*cursor)->c = 1;
        } else {
            ((*cursor)->c)++;
        }
        looper = looper->next;
    }
    if (looper != NULL) {
        looper->next = next_node;
        if (next_node != NULL) {
            next_node->prev = looper;
        }
        if (looper->c == '\n') {
            ((*cursor)->line)++;
            (*cursor)->c = 1;
        } else ((*cursor)->c)++;
    }
    (*cursor)->current_node = looper;
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
    if (*list == NULL) return;
    while ((*list)->next != NULL) {
        *list = (*list)->next;
        free((*list)->prev);
    }
    free(*list);
}

void change_cursor(cursor_t **cursor, int line, int c) {
    int aux_line = 1;
    int aux_c = 1;
    if (line == 1 && c == 1) {
        (*cursor)->current_node = (*cursor)->first;
        (*cursor)->c = 1;
        (*cursor)->line = 1;
        return;
    }
    node_t *looper = (*cursor)->first;
    while (looper != NULL) {
        if (looper->c == '\n') {
            aux_line++;
            aux_c = 1;
        } else {
            aux_c++;
        }
        if (aux_line == line && aux_c == c) {
            (*cursor)->current_node = looper;
            (*cursor)->line = line;
            (*cursor)->c = c;
            break;
        };
        if (looper->next == NULL) {
            (*cursor)->current_node = looper;
            (*cursor)->line = aux_line;
            (*cursor)->c = 1;
        }
        looper = looper->next;
    }
}

stack_node_t *generateStackNode(node_t *command, node_t *list, node_t *back, int stop, int prev_c, int prev_line) {
    stack_node_t *undo_node = (stack_node_t *) malloc(sizeof(stack_node_t));
    undo_node->command = command;
    undo_node->list = list;
    undo_node->back = back;
    undo_node->next = NULL;
    undo_node->stop = stop;
    undo_node->prev_c = prev_c;
    undo_node->prev_line = prev_line;
    return undo_node;
}

void pop_and_undo(stack_t ** undo_stack, stack_t ** redo_stack, cursor_t **cursor) {
    while ((*undo_stack)->size != 0) {
        stack_node_t *helper = (*undo_stack)->front;
        if (helper->command == NULL) {
            if (helper->list == NULL) helper->list = (*cursor)->first;
            add_to_stack(redo_stack, generateStackNode(helper->command, helper->list, helper->back, 0, (*cursor)->c, (*cursor)->line));
            if (helper->list->prev == NULL) {
                (*cursor)->first = helper->back->next;
            } else {
                helper->list->prev->next = helper->back->next;
                helper->back->next->prev = helper->list->prev;
            }
        } else {
            if (helper->stop) add_to_stack(redo_stack, generateStackNode(helper->command, NULL, NULL, 0, 0, 0));
            if (helper->list != NULL) {
                // First we free the memory of the inserted text
                node_t *looper = helper->list->prev;
                if (looper == NULL) looper = (*cursor)->first;
                else looper = looper->next;
                while(looper != helper->back->next) {
                    node_t *helper2 = looper;
                    looper = looper->next;
                    free(helper2);
                }
                if (helper->list->prev == NULL) {
                    (*cursor)->first = helper->list;
                } else {
                    helper->list->prev->next = helper->list;
                }
                if (helper->back->next != NULL) helper->back->next->prev = helper->back;
            }
        }
        change_cursor(cursor, helper->prev_line, helper->prev_c);
        if (helper->stop) {
            (*undo_stack)->front = helper->next;
            free(helper);
            ((*undo_stack)->size)--;
            break;
        }
        (*undo_stack)->front = helper->next;
        free(helper);
        ((*undo_stack)->size)--;
    }
}

void pop_and_redo(stack_t ** undo_stack, stack_t ** redo_stack, cursor_t **cursor) {
    if ((*redo_stack)->size > 0) {
        stack_node_t *helper = (*redo_stack)->front;
        if (helper->command == NULL) {
            if (helper->list->prev == NULL) {
                (*cursor)->first = helper->list;
                if (helper->back->next != NULL) {
                    helper->back->next->prev = helper->back;
                }
            } else {
                helper->list->prev->next = helper->list;
                if (helper->back->next != NULL) {
                    helper->back->next->prev = helper->back;
                }
            }
            change_cursor(cursor, helper->prev_line, helper->prev_c);

        } else {
            command_decide(undo_stack, redo_stack, helper->command, cursor, 0);
        }
        (*redo_stack)->front = (*redo_stack)->front->next;
        free_list(&(helper->command));
        free(helper);
        ((*redo_stack)->size)--;
    }
}

void empty_stack(stack_t **stack) {
    stack_node_t *helper;
    while ((*stack)->front != NULL) {
        helper = (*stack)->front;
        free_list(&(helper->list));
        free_list(&(helper->command));
        (*stack)->front = (*stack)->front->next;
        free(helper);
    }
    (*stack)->size = 0;
}

void copy_list(node_t **start, node_t **end, node_t *list) {
    node_t *looper = list;
    while (looper->c != ' ') looper = looper->next;
    looper = looper->next;
    *start = looper;
    while (looper->c != ' ' && looper->c != '\n') looper = looper->next;
    *end = looper->prev;
    looper = *start;
    node_t *helper = (node_t *) malloc(sizeof(node_t));
    helper->c = looper->c;
    helper->next = NULL;
    helper->prev = NULL;
    node_t *copy = helper;
    *start = helper;
    looper = looper->next;
    while (looper != NULL && looper != (*end)->next) {
        helper = (node_t *) malloc(sizeof(node_t));
        helper->c = looper->c;
        helper->next = NULL;
        helper->prev = copy;
        copy->next = helper;
        copy = helper;
        looper = looper->next;
    }
    *end = helper;
}

void delete_or_replace(stack_t **undo_stack, node_t *command, cursor_t **cursor, int type, int should_replace) {
    node_t *looper;
    if (type == 1) looper = (*cursor)->current_node->next->next;
    else looper = (*cursor)->first;
    node_t *search = command->next->next->next;
    node_t *replace, *replace_back;
    node_t *begin = looper;
    node_t *search_begin = search;
    int first = 1;
    while (looper != NULL) {
        if (search->c == ' ' || search->c == '\n') {
            add_to_stack(undo_stack, generateStackNode(command, begin, looper->prev, first, (*cursor)->c, (*cursor)->line));
            if (should_replace) {
                copy_list(&replace, &replace_back, search_begin);
                begin->prev->next = replace;
                replace->prev = begin->prev;
                looper->prev = replace_back;
                replace_back->next = looper;
            } else {
                begin->prev->next = looper;
                looper->prev = begin->prev;
            }
            begin = looper->next;
            first = 0;
            search = search_begin;
            if (type == 1) break;
        } else if (search->c != looper->c) {
            begin = looper->next;
            search = search_begin;
            if (search->c == looper->c) search = search->next;
        } else {
            search = search->next;
        }
        looper = looper->next;
    }
}

void command_decide(stack_t **undo_stack, stack_t **redo_stack, node_t *current_line, cursor_t ** cursor, int redo_stack_call) {
    if (current_line->c == 'u') {
        free_list(&current_line);
        pop_and_undo(undo_stack, redo_stack, cursor);
    } else if(current_line->c == 'r' && (current_line->next->c == '\n' || current_line->next->c == ' ')) {
        free_list(&current_line);
        pop_and_redo(undo_stack, redo_stack, cursor);
    } else if(current_line->c == 'q') {
        if (redo_stack_call) empty_stack(redo_stack);
    } else if(current_line->c == 'b') {
        if (redo_stack_call) empty_stack(redo_stack);
        add_to_stack(undo_stack, generateStackNode(current_line, (*cursor)->current_node->next, (*cursor)->current_node->next, 1, (*cursor)->c, (*cursor)->line));
        node_t *helper = (*cursor)->current_node->next;
        if (helper->prev != NULL) {
            helper->prev->next = helper->next;
        }
        helper->next->prev = helper->prev;
        (*cursor)->current_node = helper->prev;
        if ((*cursor)->current_node == NULL) {
            (*cursor)->first = helper->next;
            (*cursor)->current_node = helper->next;
        }
    } else if(current_line->c == 'd' && current_line->next->c == 'l') {
        if (redo_stack_call) empty_stack(redo_stack);
        int num_line = 0;
        node_t *helper = current_line->next->next->next;
        while (helper != NULL && helper->c != '\n') {
            num_line = num_line * 10 + helper->c - '0';
            helper = helper->next;
        }
        if (num_line == 0) num_line = (*cursor)->line;
        int prev_line = (*cursor)->line;
        int prev_c = (*cursor)->c;
        change_cursor(cursor, num_line, 2);
        node_t *looper = (*cursor)->current_node;
        helper = (*cursor)->current_node;
        while (looper->c != '\n') looper = looper->next;
        add_to_stack(undo_stack, generateStackNode(current_line, (*cursor)->current_node, looper, 1, prev_line, prev_c));
        if (helper->prev == NULL) {
            (*cursor)->first = looper->next;
        } else {
            helper->prev->next = looper->next;
        }
        if (looper->next != NULL) {
            looper->next->prev = helper->prev;
        }
        change_cursor(cursor, prev_line, prev_c);

    } else if(current_line->c == 'g' && current_line->next->c == 'l') {
        if (redo_stack_call) empty_stack(redo_stack);
        add_to_stack(undo_stack, generateStackNode(current_line, NULL, NULL, 1, (*cursor)->c, (*cursor)->line));
        node_t *helper = current_line->next->next->next;
        int num = 0;
        while (helper->c != '\n' && helper->c != ' ') {
            num = num * 10 + helper->c - '0';
            helper = helper->next;
        }
        change_cursor(cursor, num, 1);
    } else if(current_line->c == 'g' && current_line->next->c == 'c') {
        if (redo_stack_call) empty_stack(redo_stack);
        add_to_stack(undo_stack, generateStackNode(current_line, NULL, NULL, 1, (*cursor)->c, (*cursor)->line));
        node_t *helper = current_line->next->next->next;
        int num_c = 0, num_line = 0;
        while(helper->c != '\n' && helper->c != ' ') {
            num_c = num_c * 10 + helper->c - '0';
            helper = helper->next;
        }
        if (helper->c == ' ') helper = helper->next;
        while (helper->c != '\n' && helper->c != ' ') {
            num_line = num_line * 10 + helper->c - '0';
            helper = helper->next;
        }
        if (num_line == 0) num_line = (*cursor)->line;
        change_cursor(cursor, num_line, num_c);
    } else if(current_line->c == 'd' && (current_line->next->c == ' ' || current_line->next->c == '\n')) {
        if (redo_stack_call) empty_stack(redo_stack);
        int num = 0;
        if ((current_line->next->c == ' ' && current_line->next->next->c == '\n') || current_line->next->c == '\n') num = 1;
        else {
            node_t *helper = current_line->next->next;
            while (helper->c != '\n' && helper->c != ' ') {
                num = num * 10 + helper->c - '0';
                helper = helper->next;
            }
        }
        int index = 0;
        node_t *looper = (*cursor)->current_node->next;
        while (index != num && looper != NULL) {
            looper = looper->next;
            index++;
        }
        if ((*cursor)->c != 1 && (*cursor)->line != 1) {
            add_to_stack(undo_stack, generateStackNode(current_line, (*cursor)->current_node->next->next, looper, 1, (*cursor)->c, (*cursor)->line));
            (*cursor)->current_node->next->next = looper->next;
            looper->next->prev = (*cursor)->current_node->next;
        } else {
            add_to_stack(undo_stack, generateStackNode(current_line, (*cursor)->current_node->next, looper, 1, (*cursor)->c, (*cursor)->line));
            looper->next->prev = (*cursor)->current_node;
            (*cursor)->current_node->next = looper->next;
        }
    } else if(current_line->c == 'r' && current_line->next->c == 'e') {
        if (redo_stack_call) empty_stack(redo_stack);
        delete_or_replace(undo_stack, current_line, cursor, 1, 1);
    } else if(current_line->c == 'r' && current_line->next->c == 'a') {
        if (redo_stack_call) empty_stack(redo_stack);
        delete_or_replace(undo_stack, current_line, cursor, 2, 1);         
    } else if(current_line->c == 'd' && current_line->next->c == 'w') {
        if (redo_stack_call) empty_stack(redo_stack);            
        delete_or_replace(undo_stack, current_line, cursor, 1, 0);
    } else if(current_line->c == 'd' && current_line->next->c == 'a') {
        if (redo_stack_call) empty_stack(redo_stack);
        delete_or_replace(undo_stack, current_line, cursor, 2, 0);         
    } 
}

void save_file(node_t *start) {
    FILE *out = fopen("/home/laurentiu/Scoala/Structuri de Date/Tema 1/editor.out", "w");
    while (start != NULL) {
        fprintf(out, "%c", start->c);
        start = start->next;
    }
    fclose(out);
}

int main(int argc, char *argv[]) {
    stack_t * undo_stack = alloc_stack();
    stack_t * redo_stack = alloc_stack();
    cursor_t *cursor = (cursor_t *) malloc(sizeof(cursor_t));
    cursor->first = NULL;
    cursor->current_node = NULL;
    cursor->line = 1;
    cursor->c = 1;
    FILE *in;
    in = fopen("/home/laurentiu/Scoala/Structuri de Date/Tema 1/editor.in", "r+");
    if (in == NULL) return 1;
    char current;
    int command_mode = 0;
    node_t * current_line = NULL;
    node_t * last_front = cursor->first;
    node_t * last_back;
    int prev_c = 1;
    int prev_line = 1;
    do {
        node_t *new_char = (node_t *) malloc(sizeof(node_t));
        current = fgetc(in);
        if (feof(in)) {
            free(new_char);
            break;
        }
        new_char->c = current;
        new_char->next = NULL;
        new_char->prev = NULL;
        add_to_list(&current_line, new_char);
        if (current == '\n') {
            if (check_start_command(current_line)) {
                free_list(&current_line);
                if (!command_mode) {
                    if (last_front != NULL) last_front = last_front->next;
                    last_back = cursor->current_node;
                    add_to_stack(&undo_stack, generateStackNode(NULL, last_front, last_back, 1, prev_c, prev_line));
                    prev_c = cursor->c + 1;
                    prev_line = cursor->line;
                } else {
                    last_front = cursor->current_node;
                }
                command_mode = !command_mode;
            } else if(command_mode) {
                if (current_line->c == 's') {
                    free_list(&current_line);
                    save_file(cursor->first);
                    empty_stack(&undo_stack);
                    empty_stack(&redo_stack);
                } else if (current_line->c == 'q') {
                    free_list(&current_line);
                    empty_stack(&undo_stack);
                    empty_stack(&redo_stack);
                    break;
                } else {
                    command_decide(&undo_stack, &redo_stack, current_line, &cursor, 1);
                }
            } else {
                add_to_cursor_list(&cursor, current_line);
            }
            current_line = NULL;
        }
    } while (1);
    while (cursor->first != NULL) {
        node_t *aux = cursor->first->next;
        free(cursor->first);
        cursor->first = aux;
    }
    free(cursor);
    free(undo_stack);
    free(redo_stack);
    fclose(in);
    return 0;
}