#include <stdlib.h>
#include <numeric>

#include "helpers.h"
#include "list.h"

int cmp(const void *e1, const void *e2) {
  double d1 = *(const double *)e1;
  double d2 = *(const double *)e2;
  if (double_equals(d1, d2)) {
    return 0;
  } else if (d1 < d2) {
    return 1;
  } else {
    return -1;
  }
}

static float test_insert_sorted() {
  std::vector<double> expected(8, 1. / 8.);
  std::vector<double> results(expected.size(), 0);

  node_t *head = NULL;

  insert_sorted(&head, 1.5, cmp);

  results[0] = head && (double_equals(head->data, 1.5));
  results[1] = head && head->next == NULL;

  insert_sorted(&head, -0.75, cmp);

  results[2] = head
          && (double_equals(head->data, -0.75));
  results[3] = head
          && head->next
          && (double_equals(head->data, -0.75));
  results[4] = head
          && head->next
          && (head->next->next == NULL);

  insert_sorted(&head, 4.5, cmp);
  insert_sorted(&head, 0.0, cmp);
  insert_sorted(&head, -0.5, cmp);

  results[5] = head
          && head->next
          && (double_equals(head->next->data, -0.5));
  results[6] = head
          && head->next
          && head->next->next
          && (double_equals(head->next->next->data, 0.0));
  results[7] = head
          && head->next
          && head->next->next
          && head->next->next->next
          && (double_equals(head->next->next->next->data, 1.5));

  show_results(5.1, "insert sorted", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}


static float test_merge_sorted() {
  std::vector<double> expected(4, 1. / 4.);
  std::vector<double> results(expected.size(), 0);

  node_t *h1 = NULL;
  push_back(&h1, 1.0);
  push_back(&h1, 2.0);
  push_back(&h1, 9.0);

  node_t *h2 = NULL;
  push_back(&h2, -3.0);
  push_back(&h2, 3.0);
  push_back(&h2, 4.0);

  node_t *merged = merge_sorted(&h1, &h2, cmp);

  results[0] = merged
          && (double_equals(merged->data, -3.0));
  results[1] = merged
          && merged->next
          && (double_equals(merged->next->data, 1.0));
  results[2] = merged
          && merged->next
          && merged->next->next
          && (double_equals(merged->next->next->data, 2.0));
  results[3] = merged
          && merged->next
          && merged->next->next
          && merged->next->next->next
          && (double_equals(merged->next->next->next->data, 3.0));

  show_results(5.2, "merge sort", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

float test_exercise5() {
  std::vector<double> expected = {1.0, 1.0};
  std::vector<double> results(expected.size(), 0);

  results[0] = test_insert_sorted();
  results[1] = test_merge_sorted();

  show_results(5.0, "sort list", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
