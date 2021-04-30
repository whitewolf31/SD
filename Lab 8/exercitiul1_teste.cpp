#include <stdlib.h>
#include <numeric>

#include "exercitiul1.h"
#include "helpers.h"

static int test_sort_once(void) {
    std::vector<int> vec = generate_vec(5, 20, -50, 50);
    int *arr = (int*)calloc(vec.size(), sizeof(*arr));
    std::copy(vec.begin(), vec.end(), arr);
    std::sort(vec.begin(), vec.end());
    sort_using_pq_heaps(arr, vec.size());
    return compare_arrays(&vec[0], arr, vec.size());
}

float test_exercise1(void) {
    std::vector<double> expected(2, 3.0 / 2.0);
    std::vector<double> results(expected.size(), 0);

    results[0] = test_sort_once();
    results[1] = test_sort_once();

    show_results(1.0, "heap-sort & stl", expected, results);
    double total = 0;
    for (size_t idx = 0; idx < results.size(); idx ++) {
        total += results[idx] * expected[idx];
    }
    return total;
}
