#include "helpers.h"
#include "bst_node.h"

void traverse_in_order(bst_node_t * const root, func_t func) {
    if (root == NULL) return;
    traverse_in_order(root->left, func);
    func(root);
    traverse_in_order(root->right, func);
}

void traverse_pre_order(bst_node_t * const root, func_t func) {
    if (root == NULL) return;
    func(root);
    traverse_pre_order(root->left, func);
    traverse_pre_order(root->right, func);
}

void traverse_post_order(bst_node_t * const root, func_t func) {
    if (root == NULL) return;
    traverse_post_order(root->left, func);
    traverse_post_order(root->right, func);
    func(root);
}
