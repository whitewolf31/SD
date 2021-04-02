#include <stdlib.h>
#include <numeric>

#include "helpers.h"
#include "list.h"


static float test_middle() {
  std::vector<double> expected(4, 1. / 4.);
  std::vector<double> results(expected.size(), 0);

  node_t *h1 = NULL;
  node_t *mid_h1 = middle(h1);

  results[0] = (mid_h1 == NULL);
  push_back(&h1, 1.0);
  mid_h1 = middle(h1);
  results[1] = mid_h1 && double_equals(mid_h1->data, 1.0);
  push_back(&h1, 2.0);
  mid_h1 = middle(h1);
  results[2] = mid_h1 && double_equals(mid_h1->data, 2.0);

  push_back(&h1, 9.0);
  push_back(&h1, 11.0);
  push_back(&h1, -4.0);
  mid_h1 = middle(h1);

  results[3] = mid_h1 && double_equals(mid_h1->data, 9.0);

  show_results(6.1, "middle", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}


static float test_index() {
  std::vector<double> expected(8, 1. / 8.);
  std::vector<double> results(expected.size(), 0);

  node_t *h1 = NULL;
  node_t *node_at2 = index(h1, 2);

  results[0] = (node_at2 == NULL);
  node_at2 = index(h1, -1);
  results[1] = (node_at2 == NULL);

  push_back(&h1, 1.0);
  node_at2 = index(h1, 2);
  results[2] = (node_at2 == NULL);
  push_back(&h1, 2.0);
  push_back(&h1, 9.0);
  node_at2 = index(h1, 2);
  results[3] = node_at2 && double_equals(node_at2->data, 9.0);
  push_back(&h1, 11.0);
  push_back(&h1, -4.0);
  node_at2 = index(h1, 16);
  results[4] = node_at2 == NULL;

  node_at2 = index(h1, -1);
  results[5] = node_at2 && double_equals(node_at2->data, -4.0);
  node_at2 = index(h1, -3);
  results[6] = node_at2 && double_equals(node_at2->data, 9.0);
  node_at2 = index(h1, -8);
  results[7] = node_at2 == NULL;

  show_results(6.1, "index", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}


float test_exercise6() {
  std::vector<double> expected(2, 3. / 2.);
  std::vector<double> results(expected.size(), 0);

  results[0] = test_middle();
  results[1] = test_index();

  show_results(6.0, "indexing", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
