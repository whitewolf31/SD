#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct tree {
    short int cases[3][3];
    struct tree **children;
    size_t children_length;
    struct tree *parent;
    int depth;
    short int truth;
    int to_play;
    int who_won;
} tree_t;

typedef struct minmax_tree {
    int value;
    struct minmax_tree **children;
    size_t children_length;
    struct minmax_tree *parent;
    int depth;
} minmax_tree_t;

typedef struct queue_node {
    minmax_tree_t *tree_node;
    struct queue_node *next;
} queue_node_t;

typedef struct queue {
    queue_node_t *front;
    queue_node_t *back;
    size_t size;
} queue_t;

#endif