#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include <algorithm>
#include <string>
#include <vector>

int choice(const std::vector<int>& choices);
int double_equals(double a, double b);
bool compare_arrays(int v1[], int v2[], size_t len);
void print_vector(int buffer[], size_t vector_length);
std::vector<int> generate_vec(size_t low_size, size_t big_size, int elem_low, int elem_high);
void show_results(const float exercise_id,
                  const std::string& description,
                  const std::vector<double> &expectations,
                  const std::vector<double> &achievements);
#endif
