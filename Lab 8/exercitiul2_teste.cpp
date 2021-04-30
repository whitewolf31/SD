#include <stdlib.h>
#include <numeric>

#include "heap.h"
#include "helpers.h"
#include "scope_measurer.h"

#define DEBUG_VERBOSE 0
#define START_IDX 0
#define PAGE_SIZE 1024
#define ENABLE_STRESS_TEST 0

static float test_heap_insert() {
    std::vector<double> expected(7, 3.0 / 7.0);
    std::vector<double> results(expected.size(), 0.0);

    binary_heap_t *h = alloc_heap();
    heap_push(h, 10);
    if (DEBUG_VERBOSE) {
        printf("push %5d => ", 10); heap_print(h); printf("\n");
    }
    results[0] = h->values[START_IDX + 0] == 10
        && h->length == 1;

    heap_push(h, 20);
    if (DEBUG_VERBOSE){
        printf("push %5d => ", 20); heap_print(h); printf("\n");
    }
    results[1] = h->values[START_IDX + 0] == 10
        && h->values[START_IDX + 1] == 20
        && h->length == 2;

    heap_push(h, 30);
    if (DEBUG_VERBOSE) {
        printf("push %5d => ", 30); heap_print(h); printf("\n");
    }
    results[2] = h->values[START_IDX + 0] == 10
        && h->values[START_IDX + 1] == 20
        && h->values[START_IDX + 2] == 30
        && h->length == 3;

    heap_push(h, 50);
    if (DEBUG_VERBOSE) {
        printf("push %5d => ", 50); heap_print(h); printf("\n");
    }
    results[3] = h->values[START_IDX + 0] == 10
        && h->values[START_IDX + 1] == 20
        && h->values[START_IDX + 2] == 30
        && h->values[START_IDX + 3] == 50
        && h->length == 4;

    heap_push(h, 5);
    if (DEBUG_VERBOSE) {
        printf("push %5d => ", 5); heap_print(h); printf("\n");
    }
    results[4] = h->values[START_IDX + 0] == 5
        && h->values[START_IDX + 1] == 10
        && h->values[START_IDX + 2] == 30
        && h->values[START_IDX + 3] == 50
        && h->values[START_IDX + 4] == 20
        && h->length == 5;

    heap_push(h, 2);
    if (DEBUG_VERBOSE) {
        printf("push %5d => ", 2); heap_print(h); printf("\n");
    }
    results[5] = h->values[START_IDX + 0] == 2
        && h->values[START_IDX + 1] == 10
        && h->values[START_IDX + 2] == 5
        && h->values[START_IDX + 3] == 50
        && h->values[START_IDX + 4] == 20
        && h->values[START_IDX + 5] == 30
        && h->length == 6;

    heap_push(h, 3);
    if (DEBUG_VERBOSE) {
        printf("push %5d => ", 3); heap_print(h); printf("\n");
    }
    results[6] = h->values[START_IDX + 0] == 2
        && h->values[START_IDX + 1] == 10
        && h->values[START_IDX + 2] == 3
        && h->values[START_IDX + 3] == 50
        && h->values[START_IDX + 4] == 20
        && h->values[START_IDX + 5] == 30
        && h->values[START_IDX + 6] == 5
        && h->length == 7;

    heap_free(h);

    show_results(2.1, "insert", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_heap_top() {
    std::vector<double> expected(5, 1.0 / 5.0);
    std::vector<double> results(expected.size(), 0.0);

    binary_heap_t *h = alloc_heap();
    heap_push(h, 10);
    results[0] = heap_top(h) == 10;

    heap_push(h, 20);
    results[1] = heap_top(h) == 10;

    heap_push(h, 8);
    results[2] = heap_top(h) == 8;

    heap_push(h, 50);
    results[3] = heap_top(h) == 8;

    heap_push(h, 5);
    results[4] = heap_top(h) == 5;

    heap_free(h);

    show_results(2.2, "top", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_heap_pop() {
    std::vector<double> expected(8, 4.0 / 8.0);
    std::vector<double> results(expected.size(), 0.0);

    binary_heap_t *h = alloc_heap();
    heap_push(h, 1);
    heap_push(h, 100);
    heap_push(h, 10);
    heap_push(h, 87);
    heap_push(h, 37);
    heap_push(h, 66);
    heap_push(h, 21);
    heap_push(h, 31);
    heap_push(h, 62);
    heap_push(h, 89);

    results[0] = heap_top(h) == 1 && h->length == 10;

    heap_pop(h);
    results[1] = heap_top(h) == 10 && h->length == 9;
    if (DEBUG_VERBOSE){
        printf("pop => "); heap_print(h); printf("\n");
    }

    heap_pop(h);
    results[2] = heap_top(h) == 21 && h->length == 8;
    if (DEBUG_VERBOSE){
        printf("pop => "); heap_print(h); printf("\n");
    }

    heap_pop(h);
    results[3] = heap_top(h) == 31 && h->length == 7;
    if (DEBUG_VERBOSE){
        printf("pop => "); heap_print(h); printf("\n");
    }

    heap_pop(h);
    results[4] = heap_top(h) == 37 && h->length == 6;
    if (DEBUG_VERBOSE){
        printf("pop => "); heap_print(h); printf("\n");
    }

    heap_pop(h);
    results[5] = heap_top(h) == 62 && h->length == 5;
    if (DEBUG_VERBOSE){
        printf("pop => "); heap_print(h); printf("\n");
    }

    heap_pop(h);
    results[6] = heap_top(h) == 66 && h->length == 4;
    if (DEBUG_VERBOSE){
        printf("pop => "); heap_print(h); printf("\n");
    }

    heap_pop(h);
    results[7] = heap_top(h) == 87 && h->length == 3;
    if (DEBUG_VERBOSE){
        printf("pop => "); heap_print(h); printf("\n");
    }
    heap_free(h);

    show_results(2.3, "pop", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static int random_operation() {
    std::vector<int> operations;
    operations.push_back(0); // insert
    operations.push_back(1); // pop
    return choice(operations);

}

static float test_heap_stress() {
    std::vector<double> expected(2, 2.0 / 2.0);
    std::vector<double> results(expected.size(), 0.0);
    ScopeMeasurer push_time_measurer;
    ScopeMeasurer pop_time_measurer;
    ScopeMeasurer top_time_measurer;

    binary_heap_t *h = alloc_heap();
    std::vector<int> large_vector = generate_vec(16, PAGE_SIZE * 10 ,
        -50000, 50000);
    for (size_t idx = 0; idx < large_vector.size(); idx++) {
        push_time_measurer.startMeasure();
        heap_push(h, large_vector[idx]);
        push_time_measurer.finishMeasure();
    }

    int test1 = 1;
    std::sort(large_vector.begin(), large_vector.end());
    for (size_t idx = 0; idx < large_vector.size(); idx++) {
        top_time_measurer.startMeasure();
        int top = heap_top(h);
        top_time_measurer.finishMeasure();
        test1 &= (top == large_vector[idx]);

        pop_time_measurer.startMeasure();
        heap_pop(h);
        pop_time_measurer.finishMeasure();
    }
    results[0] = test1;
    heap_free(h);

    binary_heap_t *h2 = alloc_heap();
    std::vector<int> large_vector2 = generate_vec(PAGE_SIZE * 1000,
        PAGE_SIZE * 5000, -500000, 500000);
    for (size_t idx = 0; idx < large_vector2.size(); idx++) {
        if (random_operation() == 0) {
            push_time_measurer.startMeasure();
            heap_push(h2, large_vector2[idx]);
            push_time_measurer.finishMeasure();
        } else {
            pop_time_measurer.startMeasure();
            heap_pop(h2);
            pop_time_measurer.finishMeasure();
        }
    }

    int test2 = 1;
    int last_top = heap_top(h2);
    for (size_t idx = 0; idx < h2->length; idx++) {
        top_time_measurer.startMeasure();
        int top = heap_top(h2);
        top_time_measurer.finishMeasure();
        test2 &= (top >= last_top);
        last_top = top;
        pop_time_measurer.startMeasure();
        heap_pop(h2);
        pop_time_measurer.finishMeasure();
    }
    results[1] = test2;
    heap_free(h2);

    printf("%10s [X%15zd] [total time=%2.2lf] [average time=%2.12lf]\n",
        "push",
        push_time_measurer.getCallCount(),
        push_time_measurer.getTotalTime(),
        push_time_measurer.getAverageTime());

    printf("%10s [X%15zd] [total time=%2.2lf] [average time=%2.12lf]\n",
        "pop",
        pop_time_measurer.getCallCount(),
        pop_time_measurer.getTotalTime(),
        pop_time_measurer.getAverageTime());

    printf("%10s [X%15zd] [total time=%2.2lf] [average time=%2.12lf]\n",
        "top",
        top_time_measurer.getCallCount(),
        top_time_measurer.getTotalTime(),
        top_time_measurer.getAverageTime());

    show_results(2.4, "stress", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

float test_exercise2(void) {
    size_t test_count = 3;
    if (ENABLE_STRESS_TEST) {
        test_count = 4;
    }
    std::vector<double> expected = {3.0, 1.0, 4.0, 2.0};
    std::vector<double> results(test_count, 0);

    results[0] = test_heap_insert();
    results[1] = test_heap_top();
    results[2] = test_heap_pop();
    if (ENABLE_STRESS_TEST) {
        results[3] = test_heap_stress();
    }

    show_results(2.0, "heap", expected, results);
    double total = 0;
    for (size_t idx = 0; idx < results.size(); idx ++) {
        total += results[idx] * expected[idx];
    }
    return total;
}
