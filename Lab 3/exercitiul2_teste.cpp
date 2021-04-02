#include <stdlib.h>
#include <numeric>

#include "helpers.h"
#include "list.h"

static double power_up(const node_t *node) {
  double val = node->data;
  return val * val;
}

static float test_map() {
  std::vector<double> expected(4, 1. / 4.);
  std::vector<double> results(expected.size(), 0);

  node_t *head = NULL;

  push_front(&head, 24.45);
  map(head, power_up);

  results[0] = head && (head->data == (24.45 * 24.45));

  push_front(&head, 0.667);
  push_front(&head, 0.0);
  map(head, power_up);

  results[1] = head
            && (head->data == 0);
  results[2] = head
            && head->next
            && (head->next->data == (0.667 * 0.667));
  results[3] = head
            && head->next
            && head->next->next
            && (head->next->next->data == ((24.45 * 24.45) * (24.45 * 24.45)));

  show_results(2.1, "map", expected, results);

  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static double lessthan0(const node_t *node) {
  return -node->data;
}

static float test_filter() {
  std::vector<double> expected(4, 1. / 4.);
  std::vector<double> results(expected.size(), 0);

  node_t *head = NULL;

  push_back(&head, 24.45);
  push_back(&head, 0.667);
  push_back(&head, -0.3);
  push_back(&head, -0.667);
  push_back(&head, 0.0);

  filter(&head, lessthan0);

  results[0] = head
          && (head->data == 24.45);
  results[1] = head
          && head->next
          && (head->next->data == 0.667);
  results[2] = head
          && head->next
          && head->next->next
          && (head->next->next->data == 0.0);
  results[3] = head
          && head->next
          && head->next->next
          && (head->next->next->next == NULL);

  show_results(2.2, "filter", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static double get(const node_t *node) {
  return node->data;
}

static float test_aggregate() {
  std::vector<double> expected(2, 1. / 2.);
  std::vector<double> results(expected.size(), 0);

  node_t *head = NULL;

  push_back(&head, 24.45);
  results[0] = head && (aggregate(head, get) == 24.45);
  push_back(&head, 0.667);
  push_back(&head, -0.3);
  push_back(&head, -0.667);
  push_back(&head, 0.0);
  results[1] = head && (aggregate(head, get) == 24.15);

  show_results(2.3, "aggregate", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

float test_exercise2() {
  std::vector<double> expected = {1.0, 1.0, 1.0};
  std::vector<double> results(expected.size(), 0);

  results[0] = test_map();
  results[1] = test_filter();
  results[2] = test_aggregate();

  show_results(2.0, "functionals", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
