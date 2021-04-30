#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#include <algorithm>
#include <vector>

#include "helpers.h"

float test_exercise1();
float test_exercise2();
float test_exercise3();

static float test_caller(int test_id) {
  float points = 0;
  switch (test_id) {
    case 1:
      points = test_exercise1();
      break;
    case 2:
      points = test_exercise2();
      break;
    case 3:
      points = test_exercise3();
      break;
    default:
      printf("Exercitiul %d nu exista !\n", test_id);
      break;
  }
  printf("--------------------------------------------------------------------------------------------------------\n");
  return points;
}


int main(int argc, char **argv) {
  float total_points = 0;
  size_t exercise_count = 2;
  printf("=========================================================================================================\n");
  if (argc > 1) {
    for (int idx = 1; idx < argc; idx++) {
      int id = atoi(argv[idx]);
      total_points += test_caller(id);
    }
  } else {
    for(size_t id = 1; id <= exercise_count; id++)
      total_points += test_caller(id);
  }
  printf("=========================================================================================================\n");
  if (total_points >= 9.99) {
    printf("Felicitari, ai obtinut punctajul maxim !\n");
  }

  char line[120];
  memset(line, '.', sizeof(line));
  size_t len = sprintf(line, "Total "); line[len] = '.';
  sprintf(line + 70, " %2.2f / %2.2f", total_points, 10.0);
  printf("%s\n", line);
  printf("=========================================================================================================\n");
}
