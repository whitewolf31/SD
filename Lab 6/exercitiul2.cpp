#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "bst_node.h"
#include "helpers.h"

size_t tree_height(bst_node_t * const root) {
  if (root == NULL) return 0;
  size_t left = tree_height(root->left);
  size_t right = tree_height(root->right);
  return (left < right) ? 1 + right : 1 + left;
}

size_t node_height(bst_node_t * const node) {
  bst_node_t *looper = node;
  size_t len = 0;
  while (looper != NULL) {
    looper = looper->parent;
    len++;
  }
  return len - 1;
}
