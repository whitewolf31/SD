#include <stdlib.h>
#include <numeric>

#include "bst_node.h"
#include "helpers.h"

float test_exercise5() {
  std::vector<double> expected(3, 1.0);
  std::vector<double> results(expected.size(), 0);

  bst_node_t *root = NULL;
  insert(&root, 15.0);
  insert(&root, 23.0);
  insert(&root, 7.0 );
  insert(&root, 13.0);
  insert(&root, 1.0 );
  insert(&root, 20.0);
  insert(&root, 27.0);
  insert(&root, 21.0);
  insert(&root, 24.0);
  insert(&root, 22.0);
  insert(&root, 23.0);
  insert(&root, 25.0);
  insert(&root, 26.0);

  results[0] = (diameter(root) == 9);
  results[1] = (root && diameter(root->left) == 3);
  results[2] = (root && root->right && diameter(root->right->left) == 4);

  show_results(5.0, "diameter", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
