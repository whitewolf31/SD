#include "cerinte.h"

void read_num(FILE *in, int *num) {
    char helper;
    int factor = 1;
    *num = 0;
    helper = fgetc(in);
    if (helper == '-') factor = -1;
    else *num = helper - '0'; 
    while (1) {
        helper = fgetc(in);
        if (helper < '0' || helper > '9') break;
        *num = *num * 10 + helper - '0';
    }
    *num = *num * factor;
}

void add_to_queue(queue_t *queue, queue_node_t *node) {
    if (queue == NULL) return;
    if (queue->size == 0) {
        queue->front = node;
    } else {
        queue_node_t *looper = queue->front;
        while (looper->next != NULL) looper = looper->next;
        looper->next = node;
    }
    (queue->size)++;
}

minmax_tree_t *pop_from_queue(queue_t *queue) {
    if (queue->size == 0) return NULL;
    minmax_tree_t *helper1 = queue->front->tree_node;
    queue_node_t *helper2 = queue->front;
    queue->front = queue->front->next;
    free(helper2);
    (queue->size)--;
    return helper1;
}

void create_tree_nodes(queue_t *queue, int is_interior_node, int value, int depth) {
    minmax_tree_t *current_tree_node = pop_from_queue(queue);
    current_tree_node->depth = depth;
    if (!is_interior_node) {
        current_tree_node->value = value;
        current_tree_node->children_length = 0;
    }
    else {
        current_tree_node->children = (minmax_tree_t **) malloc(value * sizeof(minmax_tree_t*));
        current_tree_node->children_length = value;
        for (int i = 0; i < value; i++) {
            current_tree_node->children[i] = (minmax_tree_t *) malloc(sizeof(minmax_tree_t));
            current_tree_node->children[i]->children = NULL;
            current_tree_node->children[i]->parent = current_tree_node;
            queue_node_t *queue_node = (queue_node_t *) malloc(sizeof(queue_node_t));
            queue_node->tree_node = current_tree_node->children[i];
            queue_node->next = NULL;
            add_to_queue(queue, queue_node);
        }
    }
}

void build_minmax_tree(minmax_tree_t *tree_node) {
    if (tree_node->children_length == 0) return;
    int cmp_val;
    for (int i = 0; i < tree_node->children_length; i++) {
        build_minmax_tree(tree_node->children[i]);
        if (i == 0) cmp_val = tree_node->children[i]->value;
        else {
            if (tree_node->depth % 2 == 0) {
                if (tree_node->children[i]->value > cmp_val) cmp_val = tree_node->children[i]->value;
            } else {
                if (tree_node->children[i]->value < cmp_val) cmp_val = tree_node->children[i]->value;
            }
        } 
    }
    tree_node->value = cmp_val;
}

void output_minmax_tree(minmax_tree_t *tree_node, FILE *out) {
    for (int i = 0; i < tree_node->depth; i++) fputc('\t', out);
    fprintf(out, "%d\n", tree_node->value);
    for (int i = 0; i < tree_node->children_length; i++) {
        output_minmax_tree(tree_node->children[i], out);
    }
    if (tree_node->children != NULL) free(tree_node->children);
    free(tree_node);
}

void main_cerinta3(int argc, char *argv[]) {
    FILE *in, *out;
    in = fopen(argv[2], "r");
    out = fopen(argv[3], "w");
    minmax_tree_t *tree_root = (minmax_tree_t*) malloc(sizeof(minmax_tree_t));
    tree_root->children = NULL;
    tree_root->children_length = 0;
    tree_root->depth = 0;
    tree_root->parent = NULL;
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
    queue->front = NULL;
    queue->size = 0;
    queue_node_t *queue_node = (queue_node_t *) malloc(sizeof(queue_node_t));
    queue_node->tree_node = tree_root;
    queue_node->next = NULL;
    add_to_queue(queue, queue_node);
    int depth, is_interior_node, value;
    fscanf(in, "%d\n", &depth);
    for (int i = 0; i < depth; i++) {
        while (1) {
            is_interior_node = 0;
            char helper = fgetc(in);
            if (helper == '(') is_interior_node = 1;
            read_num(in, &value);
            create_tree_nodes(queue, is_interior_node, value, i);
            helper = fgetc(in);
            if (helper == '\n') break;
        }
    }
    build_minmax_tree(tree_root);
    output_minmax_tree(tree_root, out);
    free(queue);
    fclose(in);
    fclose(out);
}