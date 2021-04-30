#ifndef __BST_NODE_H__
#define __BST_NODE_H__

#include <stdbool.h>

typedef struct bst_node {
    double value;

    struct bst_node *parent;
    struct bst_node *left;
    struct bst_node *right;
} bst_node_t;

bst_node_t init_bst_node(const double value);
bst_node_t *alloc_bst_node(const double value);
void insert(bst_node_t *&root, const double value);
size_t tree_height(bst_node_t * const root);
void print_tree(const bst_node_t *root);

// exercitiul 1
char *serialize(const bst_node_t *root);
bst_node_t *deserialize(const char *serialized_tree);

//exercitiul 2
size_t height(const bst_node_t *root);
void rotate_left(bst_node_t *&root);
void rotate_right(bst_node_t *&root);
void insert_avl(bst_node_t *&root);

#endif
