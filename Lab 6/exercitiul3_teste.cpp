#include <stdlib.h>
#include <numeric>

#include "bst_node.h"
#include "helpers.h"

static int run_inorder = 0;
static int inorder_ok = 1;
static double in_order_values[] = {1, 7, 13, 15, 20, 23, 27};
static void in_order_print(bst_node_t * const node) {
  static size_t idx = 0;
  size_t n = sizeof(in_order_values) / sizeof(in_order_values[0]);
  if (idx >= n - 1) {
    run_inorder = 1;
    return;
  }
  if (!node) {
    return;
  }
  inorder_ok &= (node && (in_order_values[idx] == node->value));
  idx++;
}

static int run_preorder = 0;
static int preorder_ok = 1;
static double pre_order_values[] = {15, 7, 1, 13, 23, 20, 27};
static void pre_order_print(bst_node_t * const node) {
  static size_t idx = 0;
  size_t n = sizeof(in_order_values) / sizeof(in_order_values[0]);
  if (idx >= n - 1) {
    run_preorder = 1;
    return;
  }
  if (!node) {
    return;
  }
  preorder_ok &= (node && (pre_order_values[idx] == node->value));
  idx++;
}

static int run_postorder = 0;
static int postorder_ok = 1;
static double post_order_values[] = {1, 13, 7, 20, 27, 23, 15};
static void post_order_print(bst_node_t * const node) {
  static size_t idx = 0;
  size_t n = sizeof(in_order_values) / sizeof(in_order_values[0]);
  if (idx >= n - 1) {
    run_postorder = 1;
    return;
  }
   if (!node) {
    return;
  }
  postorder_ok &= (post_order_values[idx] == node->value);
  idx++;
}

float test_exercise3() {
  std::vector<double> expected = {1.0, 1.0, 1.0};
  std::vector<double> results(expected.size(), 0);

  bst_node_t *root = NULL;
  insert(&root, 15.0);
  insert(&root, 23.0);
  insert(&root, 7.0 );
  insert(&root, 13.0);
  insert(&root, 1.0 );
  insert(&root, 20.0);
  insert(&root, 27.0);

  traverse_in_order(root, in_order_print);
  results[0] = run_inorder && inorder_ok;
  traverse_pre_order(root, pre_order_print);
  results[1] = run_preorder && preorder_ok;
  traverse_post_order(root, post_order_print);
  results[2] = run_postorder && postorder_ok;

  show_results(3.0, "traversals", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
