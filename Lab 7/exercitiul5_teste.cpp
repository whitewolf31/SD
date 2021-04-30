#include <stdlib.h>
#include <numeric>

#include "bst_node.h"
#include "helpers.h"

float test_exercise5() {
  std::vector<double> expected(3, 1.0);
  std::vector<double> results(expected.size(), 0);

  show_results(5.0, "diameter", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
