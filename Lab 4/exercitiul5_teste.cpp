#include <stdlib.h>

#include "helpers.h"
#include "list.h"


float test_exercise5() {
  int value = 10;
  node_t *current = new_node(&value, sizeof(value));

  value = 20;
  node_t *up = new_node(&value, sizeof(value));

  value = 30;
  node_t *down = new_node(&value, sizeof(value));

  value = 40;
  node_t *left = new_node(&value, sizeof(value));

  value = 50;
  node_t *right = new_node(&value, sizeof(value));

  swap_with_neighbour(current, left, up, right, down, UP);
  float test1 = get_int_value(current) == 20 && get_int_value(up) == 10;

  swap_with_neighbour(current, left, up, right, down, DOWN);
  float test2 = get_int_value(current) == 30 && get_int_value(down) == 20;

  swap_with_neighbour(current, left, up, right, down, LEFT);
  float test3 = get_int_value(current) == 40 && get_int_value(left) == 30;

  swap_with_neighbour(current, left, up, right, down, RIGHT);
  float test4 = get_int_value(current) == 50 && get_int_value(right) == 40;


  int results[] = {(int)test1, (int)test2, (int)test3, (int)test4};
  int results_len = sizeof(results) / sizeof(results[0]);
  float points = (test1 + test2 + test3 + test4) / results_len;

  show_results(5, 2.0, points * 2.0, results, results_len);
  return points * 2.0;
}
