#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include <algorithm>
#include <vector>

int double_equals(double a, double b);

int compare_arrays(int v1[], int v2[], size_t len);

void print_vector(int buffer[], size_t vector_length);

std::vector<int> generate_vec(size_t low_size, size_t big_size, int elem_low, int elem_high);

void show_results(const float exercise,
                  const double expected,
                  const double achieved,
                  const int test_results[],
                  const size_t test_count);
#endif
