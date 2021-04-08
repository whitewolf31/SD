#ifndef __BST_NODE_H__
#define __BST_NODE_H__


typedef struct bst_node {
    double value;

    struct bst_node *parent;
    struct bst_node *left;
    struct bst_node *right;
} bst_node_t;

bst_node_t init_bst_node(const double value);
bst_node_t *alloc_bst_node(const double value);
void print_tree(const bst_node_t *root);

// exercitiul 1
void insert(bst_node_t **root, const double value);
void remove(bst_node_t **root, const double value);
bst_node_t *search(bst_node_t * const root, const double value);

//exercitiul2
size_t tree_height(bst_node_t * const root);
size_t node_height(bst_node_t * const node);

//exercitiul3
typedef void (*func_t)(bst_node_t * const node);

void traverse_in_order(bst_node_t * const root, func_t func);
void traverse_pre_order(bst_node_t * const root, func_t func);
void traverse_post_order(bst_node_t * const root, func_t func);

// exercitiul4
bst_node_t *lowest_common_ancestor(
  bst_node_t * const node1,
  bst_node_t * const node2
);

//exercitiul5
size_t diameter(bst_node_t * const node);

#endif
