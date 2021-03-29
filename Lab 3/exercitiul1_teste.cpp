#include <stdlib.h>
#include <numeric>

#include "helpers.h"
#include "list.h"

static float test_push_front() {
  std::vector<double> expected(3, 1./3.);
  std::vector<double> results(expected.size(), 0);

  node_t *head = NULL;

  push_front(&head, 24.45);
  results[0] = head && (head->data == 24.45);
  push_front(&head, 0.667);
  results[1] = head && (head->data == 0.667);
  push_front(&head, 0.0);
  results[2] = head && (head->data == 0.0);

  show_results(1.1, "push_front", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_push_back() {
  std::vector<double> expected(3, 1./3.);
  std::vector<double> results(expected.size(), 0);

  node_t *head = NULL;

  push_back(&head, 24.45);
  results[0] = head && (head->data == 24.45);
  push_back(&head, 0.667);
  results[1] = head && (head->data == 24.45);
  push_back(&head, 0.0);

  if (head) {
    while(head->next) {
      head = head->next;
    }
  }
  results[2] = head && (head->data == 0.0);

  show_results(1.2, "push_back", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

float test_exercise1() {
  std::vector<double> expected = {1.0, 1.0};
  std::vector<double> results(expected.size(), 0);

  results[0] = test_push_front();
  results[1] = test_push_back();

  show_results(1.0, "list insertion", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;

}
