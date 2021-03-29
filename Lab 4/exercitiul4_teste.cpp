#include <stdlib.h>

#include "helpers.h"
#include "list.h"

float test_exercise4() {
  int value = 30;
  node_t *node = NULL;
  node_t *head = new_node(&value, sizeof(value));;

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  value = 10;
  node = new_node(&value, sizeof(value));
  push_back(head, node);

  value = 20;
  node = new_node(&value, sizeof(value));
  push_back(head, node);

  value = 30;
  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  value = 25;
  node = new_node(&value, sizeof(value));
  push_back(head, node);

  value = 30;
  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node = new_node(&value, sizeof(value));
  push_back(head, node);

  value = 20;
  node = new_node(&value, sizeof(value));
  push_back(head, node);

  value = 10;
  node = new_node(&value, sizeof(value));
  push_back(head, node);

  size_t removed = remove_equal_sequence(head, NULL, get_int_value);

  int test1 = removed == 14 
            && head && (get_int_value(head) == 10)
            && head->next && (get_int_value(head->next) == 20)
            && head->next->next && (get_int_value(head->next->next) == 25)
            && head->next->next->next && (get_int_value(head->next->next->next) == 20)
            && head->next->next->next->next && (get_int_value(head->next->next->next->next) == 10)
            && head->next->next->next->next->next == NULL;

  int results[] = {test1};
  int results_len = sizeof(results) / sizeof(results[0]);
  float points = test1 / results_len;

  show_results(4.0, 3.0, 3.0 * points, results, results_len);

  return 3.0 * points;
}
