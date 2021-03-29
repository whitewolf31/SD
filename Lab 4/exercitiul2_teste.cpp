#include <stdlib.h>

#include "helpers.h"
#include "list.h"

static float test_remove() {
  int value = 10;
  node_t *head = new_node(&value, sizeof(value));;

  value = 20;
  node_t *node = new_node(&value, sizeof(value));
  push_back(head, node);

  value = 30;
  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node_t *to_remove = head->next;
  remove(to_remove);
  int test1 = head && (get_int_value(head) == 10)
            && head->next && (get_int_value(head->next) == 30);

  to_remove = head->next;
  remove(to_remove);
  int test2 = head && (get_int_value(head) == 10) && head->next == NULL;

  remove(head);
  int test3 = head == NULL;

  float points = test1 + test2 + test3;
  int results[] = {test1, test2, test3};
  int results_len = sizeof(results) / sizeof(results[0]);

  show_results(2.1, 1.0, points / results_len, results, results_len);

  return points / results_len;
}


static float test_nth_element() {
  int value = 10;
  node_t *head = new_node(&value, sizeof(value));;

  value = 20;
  node_t *node = new_node(&value, sizeof(value));
  push_back(head, node);

  value = 30;
  node = new_node(&value, sizeof(value));
  push_back(head, node);

  node_t *node_at_0 = nth_element(head, 0);
  node_t *node_at_1 = nth_element(head, 1);
  node_t *node_at_2 = nth_element(head, 2);
  node_t *node_at_100 = nth_element(head, 100);

  int test1 = node_at_0 && (get_int_value(node_at_0) == 10);
  int test2 = node_at_1 && (get_int_value(node_at_1) == 20);
  int test3 = node_at_2 && (get_int_value(node_at_2) == 30);
  int test4 = node_at_100 && (get_int_value(node_at_100) == 30);

  float points = test1 + test2 + test3 + test4;
  int results[] = {test1, test2, test3, test4};
  int results_len = sizeof(results) / sizeof(results[0]);

  show_results(2.2, 1.0, points / results_len, results, results_len);

  return points / results_len;
}


float test_exercise2() {
  float test1 = test_remove();
  float test2 = test_nth_element();

  float points = test1 + test2;
  int results[] = {(int)test1, (int)test2};
  int results_len = sizeof(results) / sizeof(results[0]);

  show_results(2, 2.0, points, results, results_len);
  return points;
}
