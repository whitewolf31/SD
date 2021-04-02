#include <stdlib.h>
#include <numeric>

#include "helpers.h"
#include "list.h"

float test_exercise4() {
  std::vector<double> expected(3, 1.0);
  std::vector<double> results(expected.size(), 0);

  node_t *head = NULL;
  push_front(&head, -1.0);
  push_front(&head, -2.0);
  push_front(&head, 1.0);

  reverse(&head);
  results[0] = head
            && double_equals(head->data, -1.0);
  results[1] = head
            && head->next
            && double_equals(head->next->data, -2.0);
  results[2] = head
            && head->next
            && head->next->next
            && double_equals(head->next->next->data, 1.0);

  node_t *head2 = NULL;
  push_front(&head2, -1.0);

  reverse(&head2);
  results[3] = head2 && (head2->data == -1.0);
  results[4] = head2 && head2->next == NULL;

  node_t *head3 = NULL;
  reverse(&head3);
  results[5] = (head3 == NULL);

  show_results(4.0, "reverse", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
