#include <stdlib.h>
#include <numeric>

#include "bst_node.h"
#include "helpers.h"

static float test_height() {
  std::vector<double> expected(2, 1.0 / 2.0);
  std::vector<double> results(expected.size(), 0.0);


  show_results(3.1, "height", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_rotate_left() {
  std::vector<double> expected(3, 1.0 / 3.0);
  std::vector<double> results(expected.size(), 0.0);


  show_results(3.2, "rotate left", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_rotate_right() {
  std::vector<double> expected(3, 1.0 / 3.0);
  std::vector<double> results(expected.size(), 0.0);


  show_results(3.3, "rotate right", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_insert() {
  std::vector<double> expected(3, 2.0 / 3.0);
  std::vector<double> results(expected.size(), 0.0);


  show_results(3.4, "insert", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

float test_exercise3() {
  std::vector<double> expected = {1.0, 1.0, 1.0, 2.0};
  std::vector<double> results(expected.size(), 0);

  results[0] = test_height();
  results[1] = test_rotate_left();
  results[2] = test_rotate_right();
  results[3] = test_insert();

  show_results(3.0, "AVL", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
