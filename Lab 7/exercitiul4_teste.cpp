#include <stdlib.h>
#include <numeric>

#include "bst_node.h"
#include "helpers.h"

float test_exercise4() {
  std::vector<double> expected(4, 2.0 / 4);
  std::vector<double> results(expected.size(), 0);


  show_results(4.0, "lowest ca", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
