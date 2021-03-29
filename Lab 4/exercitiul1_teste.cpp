#include <stdlib.h>

#include "helpers.h"
#include "list.h"

static float test_push_after() {
  int value = 10;
  node_t *head = new_node(&value, sizeof(value));;

  value = 20;
  node_t *node = new_node(&value, sizeof(value));
  push_after(head, node);
  int test1 = head && (get_int_value(head) == 10)
            && head->next && (get_int_value(head->next) == value);

  value = 30;
  node = new_node(&value, sizeof(value));
  push_after(head, node);
  int test2 = head && (get_int_value(head) == 10)
              && head->next && (get_int_value(head->next) == 30)
              && head->next->next && (get_int_value(head->next->next) == 20);

  float points = test1 + test2;
  int results[] = {test1, test2};
  int results_len = sizeof(results) / sizeof(results[0]);

  show_results(1.1, 1.0, points / results_len, results, results_len);

  return points / results_len;
}

static float test_push_front() {
  node_t *head = NULL;

  int value = 10;
  node_t *node = new_node(&value, sizeof(value));
  push_front(head, node);
  int test1 = head && (get_int_value(head) == value);

  value = 20;
  node = new_node(&value, sizeof(value));
  push_front(head, node);
  int test2 = head && (get_int_value(head) == value)
              && head->next && (get_int_value(head->next) == 10);

  value = 30;
  node = new_node(&value, sizeof(value));
  push_front(head, node);

  int test3 = head && (get_int_value(head) == value)
              && head->next && (get_int_value(head->next) == 20)
              && head->next->next && (get_int_value(head->next->next) == 10);

  float points = test1 + test2 + test3;
  int results[] = {test1, test2, test3};
  int results_len = sizeof(results) / sizeof(results[0]);

  show_results(1.2, 1.0, points / 3.0, results, results_len);

  return points / 3.0;
}

static float test_push_back() {
  node_t *head = NULL;

  int value = 10;
  node_t *node = new_node(&value, sizeof(value));
  push_back(head, node);
  int test1 = head && (get_int_value(head) == 10);

  value = 20;
  node = new_node(&value, sizeof(value));
  push_back(head, node);
  int test2 = head && (get_int_value(head) == 10)
              && head->next && (get_int_value(head->next) == 20);

  value = 30;
  node = new_node(&value, sizeof(value));
  push_back(head, node);

  //print_list(head);
  int test3 = head && (get_int_value(head) == 10)
              && head->next && (get_int_value(head->next) == 20)
              && head->next->next && (get_int_value(head->next->next) == 30);


  float points = test1 + test2 + test3;
  int results[] = {test1, test2, test3};
  int results_len = sizeof(results) / sizeof(results[0]);

  show_results(1.3, 1.0, points / 3.0, results, results_len);

  return points / 3.0;
}

float test_exercise1() {
  int test1 = test_push_after();
  int test2 = test_push_front();
  int test3 = test_push_back();

  int results[] = {test1, test2, test3};
  int results_len = sizeof(results) / sizeof(results[0]);
  float percentage = (test1 + test2 + test3) / results_len;

  const float expected = 3.0;
  show_results(1, expected, percentage * expected, results, results_len);
  return percentage * expected;
}
