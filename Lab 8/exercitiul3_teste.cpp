#include <stdlib.h>
#include <numeric>

#include "heap.h"
#include "helpers.h"

static float test_remove1() {
    std::vector<double> expected(1, 1.0 / 1.0);
    std::vector<double> results(expected.size(), 0.0);

    binary_heap_t *h = alloc_heap();

    heap_push(h, 1);
    heap_push(h, 31);
    heap_push(h, 10);
    heap_push(h, 37);
    heap_push(h, 87);
    heap_push(h, 66);
    heap_push(h, 21);
    heap_push(h, 100);
    heap_push(h, 62);
    heap_push(h, 89);

    heap_remove(h, 66);

    int test_heap = 1;
    int test_removed_missing = 1;
    int last_top = heap_top(h);
    size_t l = h->length;

    for (size_t idx = 0; idx < l; idx++) {
        printf("%d\n", heap_top(h));
        test_heap &= (heap_top(h) >= last_top);
        test_removed_missing &= (heap_top(h) != 66);
        last_top = heap_top(h);
        heap_pop(h);
    }
    heap_free(h);

    results[0] = test_heap && test_removed_missing && l;

    return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_remove2() {
    std::vector<double> expected(1, 1.0 / 1.0);
    std::vector<double> results(expected.size(), 0.0);

    binary_heap_t *h = alloc_heap();

    heap_push(h, 1);
    heap_push(h, 31);
    heap_push(h, 10);
    heap_push(h, 37);
    heap_push(h, 87);
    heap_push(h, 66);
    heap_push(h, 21);
    heap_push(h, 100);
    heap_push(h, 62);
    heap_push(h, 89);

    heap_remove(h, 31);

    int test_heap = 1;
    int test_removed_missing = 1;
    int last_top = heap_top(h);
    size_t l = h->length;

    for (size_t idx = 0; idx < l; idx++) {
        test_heap &= (heap_top(h) >= last_top);
        test_removed_missing &= (heap_top(h) != 31);
        last_top = heap_top(h);
        heap_pop(h);
    }
    heap_free(h);

    results[0] = test_heap && test_removed_missing && l;

    return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

float test_exercise3() {
    std::vector<double> expected(2, 3.0 / 2.0);
    std::vector<double> results(expected.size(), 0);

    results[0] = test_remove1();
    results[1] = test_remove2();

    show_results(3.0, "heap_remove", expected, results);
    double total = 0;
    for (size_t idx = 0; idx < results.size(); idx ++) {
        total += results[idx] * expected[idx];
    }
    return total;
}
