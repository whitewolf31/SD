#include <stdlib.h>
#include <numeric>

#include "bst_node.h"
#include "helpers.h"

float test_exercise4() {
  std::vector<double> expected(4, 2.0 / 4);
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

  bst_node_t *n1 = search(root, 1);
  bst_node_t *n2 = search(root, 1);
  bst_node_t *lca = lowest_common_ancestor(n1, n2);
  results[0] = (lca && lca->value == 1);

  n1 = search(root, 21);
  n2 = search(root, 24);
  lca = lowest_common_ancestor(n1, n2);
  results[1] = (lca && lca->value == 23);

  n1 = search(root, 1);
  n2 = search(root, 21);
  lca = lowest_common_ancestor(n1, n2);
  results[2] = (lca && lca->value == 15);

  n1 = search(root, 7);
  n2 = search(root, 20);
  lca = lowest_common_ancestor(n1, n2);
  results[3] = (lca && lca->value == 15);

  show_results(4.0, "lowest ca", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
