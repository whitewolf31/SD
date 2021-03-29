#include <stdlib.h>

#include "helpers.h"
#include "list.h"

float test_exercise6() {
  int value = 30;
  node_t *head = NULL;
  node_t *node = NULL;

  value = 30;
  node = new_node(&value, sizeof(value));
  insert_circular(&head, node);

  int test1 = head && head->next == head && head->prev == head && get_int_value(head) == 30;

  value = 10;
  node = new_node(&value, sizeof(value));
  insert_circular(&head, node);
  int test2 = head
            && head->next && head->next->next == head
            && head->prev && head->prev->prev == head
            && head->prev == head->next
            && get_int_value(head) == 10 && get_int_value(head->next) == 30;

  value = 20;
  node = new_node(&value, sizeof(value));
  insert_circular(&head, node);

  int test3 = head
            && head->next && head->next->next && head->next->next->next == head
            && head->prev && head->prev->prev && head->prev->prev->prev == head
            && get_int_value(head) == 20
            && get_int_value(head->next) == 10
            && get_int_value(head->prev) == 30;

  int results[] = {test1, test2, test3};
  int results_len = sizeof(results) / sizeof(results[0]);
  float points = 1.0 * (test1 + test2 + test3) / results_len;

  show_results(6.0, 3.0, 3.0 * points, results, results_len);

  return 3.0 * points;
}
