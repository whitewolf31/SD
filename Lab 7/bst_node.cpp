#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include "bst_node.h"

bst_node_t init_bst_node(const double value) {
  bst_node_t r = {
      .value = value,
      .parent = NULL,
      .left = NULL,
      .right = NULL,
  };
  return r;
}

bst_node_t *alloc_bst_node(const double value) {
  bst_node_t *bst_node = (bst_node_t *)calloc(1, sizeof(*bst_node));
  *bst_node = init_bst_node(value);
  return bst_node;
}

void print_tree(const bst_node_t *root) {
  if (!root) {
    printf("null");
  } else {
    printf("[");
    print_tree(root->left);
    printf(" (%.2lf) ", root->value);
    print_tree(root->right);
    printf("]");
  }
}


static bst_node_t *last_root = NULL;
void insert(bst_node_t *&root, const double value) {
  if (!root) {
    root = alloc_bst_node(value);
    root->parent = last_root;
    last_root = NULL;
    return;
  }

  last_root = root;
  if (root->value >= value) {
    insert(root->left, value);
  } else {
    insert(root->right, value);
  }
}

size_t tree_height(bst_node_t * const root) {
  if (!root) {
    return 0;
  } else {
    return 1 + std::max(tree_height(root->left), tree_height(root->right));
  }
}
