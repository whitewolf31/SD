#include <stdlib.h>
#include <numeric>

#include "helpers.h"
#include "list.h"

float test_exercise3() {
  std::vector<double> expected(3, 2. / 3.);
  std::vector<double> results(expected.size(), 0);

  node_t *head = NULL;
  push_front(&head, -1.0);
  push_front(&head, -2.0);
  push_front(&head, 1.0);

  node_t *head2 = NULL;
  push_front(&head2, -4.0);
  push_front(&head2, -2.0);
  push_front(&head2, 0.0);

  node_t *inter1 = intersection(head, head2);
  results[0] = head && head2 && inter1 && (inter1->data == -2.0);
  results[1] = head && head2 && inter1 && (inter1->next == NULL);

  node_t *head3 = NULL;
  node_t *inter2 = intersection(head, head3);
  results[2] = head && head2 && inter2 == NULL;


  node_t *head4 = NULL;
  push_front(&head2, -4.0);
  push_front(&head2, -18.0);
  push_front(&head2, 0.0);

  node_t *inter3 = intersection(head, head4);
  results[3] = inter3 == NULL;

  show_results(3.0, "intersection", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
