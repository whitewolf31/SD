#include <stdlib.h>

#include "helpers.h"
#include "list.h"

static int power(node_t const* node) {
  if (!node) {
    return 0;
  }
  int val =  *(int *)node->data;
  return val * val;
}

float test_exercise3() {
  int value = 10;
  node_t *head = new_node(&value, sizeof(value));;

  value = 20;
  node_t *node = new_node(&value, sizeof(value));
  push_after(head, node);

  value = 30;
  node = new_node(&value, sizeof(value));
  push_after(head, node);

  apply(head, node, power);

  int test1 = head && (get_int_value(head) == 100)
            && head->next && (get_int_value(head->next) == 900)
            && head->next->next && (get_int_value(head->next->next) == 20)
            && head->next->next->next == NULL;

  int results[] = {test1};
  int results_len = sizeof(results) / sizeof(results[0]);
  float points = test1 / results_len;

  show_results(3.0, 2.0, 2.0 * points, results, results_len);

  return 2.0 * points;
}
