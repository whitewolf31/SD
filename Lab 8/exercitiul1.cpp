#include "exercitiul1.h"

#include <queue>
#include <stdio.h>


void sort_using_pq_heaps(int *values, size_t length) {
    std::priority_queue<int> pq;
    printf("%ld\n", length);
    for (int i = 0; i < length; i++) {
        pq.push(values[i]);
    }
    for (int i = length - 1; i >= 0; i--) {
        values[i] = pq.top();
        pq.pop();
    }
}
