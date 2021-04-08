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
