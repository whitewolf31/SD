#include <iostream>
#include <numeric>
#include <stdlib.h>

#include "bst_node.h"
#include "helpers.h"

static float test_tree_height() {
  std::vector<double> expected(2, 1.0 / 2.0);
  std::vector<double> results(expected.size(), 0.0);

  bst_node_t *root = NULL;
  insert(&root, 15.0);
  results[0] = (tree_height(root) == 1);
  insert(&root, 23.0);
  insert(&root, 7.0);
  insert(&root, 13.0);
  insert(&root, 20.0);

  results[1] = (tree_height(root) == 3);

  show_results(2.1, "tree_height", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_node_height() {
  std::vector<double> expected(3, 1.0 / 3.0);
  std::vector<double> results(expected.size(), 0.0);

  bst_node_t *root = NULL;
  insert(&root, 15.0);
  results[0] = (root && node_height(root) == 0);
  insert(&root, 23.0);
  insert(&root, 7.0);
  insert(&root, 13.0);
  insert(&root, 20.0);

  if (root)
    results[1] = (node_height(root->left) == 1);

  if (root && root->left)
    results[2] = (node_height(root->left->right) == 2);

  show_results(2.1, "node_height", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

float test_exercise2() {
  std::vector<double> expected = {1.0, 1.0};
  std::vector<double> results(2, 0);

  results[0] = test_tree_height();
  results[1] = test_node_height();
  show_results(2.0, "heights", expected, results);

  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
