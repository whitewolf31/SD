#include <string>
#include "helpers.h"

int double_equals(double a, double b)
{
    return fabs(a - b) < 0.0001;
}

int compare_arrays(int v1[], int v2[], size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (v1[i] != v2[i]) {
      return 0;
    }
  }
  return 1;
}

void print_vector(int buffer[], size_t vector_length) {
    printf("[");
    for (size_t index = 0; index < vector_length; index++) {
        printf("%d", buffer[index]);
        if (index < vector_length - 1)
            printf(", ");
    }
    printf("]\n");
}


std::vector<int> generate_vec(size_t low_size, size_t big_size, int elem_low, int elem_high) {
  srand(rand());
  float size_range = big_size - low_size;
  size_t vector_size = size_range * rand() / (RAND_MAX + 1.0) + low_size;
  float elem_range = elem_high - elem_low;
  std::vector<int> vec;
  for (size_t index = 0; index < vector_size; index++) {
    int elem = elem_range * rand() / (RAND_MAX + 1.0) + elem_low;
    vec.push_back(elem);
  }

  return vec;
}

void show_results(const float exercise,
                  const std::string& details,
                  const std::vector<double>& expectations,
                  const std::vector<double>& achievements) {
  double expected = 0.0;
  double achieved = 0.0;

  for (size_t idx = 0; idx < expectations.size(); idx++) {
    expected += expectations[idx];
    achieved += (expectations[idx] * achievements[idx]);
  }

  char line[120];
  memset(line, '.', sizeof(line));
  size_t len1 = sprintf(line, "Exercitiul %0.1f (%s) ", exercise, details.c_str());line[len1] = '.';
  sprintf(line + 70, " %0.2lf / %0.2lf", achieved, expected);
  printf("%s\t", line);
  if (!double_equals(achieved, expected)) {
    printf(" [");
    for (size_t idx = 0; idx < expectations.size(); idx++) {
      printf("%d", (int)achievements[idx]);
      if (idx < expectations.size() - 1)
        printf(" ");
    }
    printf("]");
  }
  printf("\n");
}
