#include <string.h>
#include <stdio.h>

#include "heap.h"
#include "helpers.h"

void swap_values(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void heap_push(binary_heap_t * const heap, const int value) {
    if (heap->length + 1 > heap->capacity) {
        heap->capacity += 1;
        heap->values = (int *) realloc(heap->values, heap->capacity);
    }
    heap->values[heap->length] = value;
    heap->length += 1;
    int *values = heap->values;
    int current_index = heap->length - 1;
    while (current_index != 0 && values[(current_index - 1)/2] > value) {
        swap_values(&(values[(current_index - 1)/2]), &(values[current_index]));
        current_index = (current_index - 1) / 2;
    }
}

int heap_top(binary_heap_t const * const heap) {
    if (heap->length == 0) return -1;
    return heap->values[0];
}

void heapify(binary_heap_t * const heap, const int index) {
    int *to_compare;
    int new_index;
    if (index * 2 + 1 >= heap->length) return;
    else if (index * 2 + 2 >= heap->length) {
        to_compare = &(heap->values[index * 2 + 1]);
        new_index = index * 2 + 1;
    } else {
        if (heap->values[index * 2 + 1] < heap->values[index * 2 + 2]) {
            to_compare = &(heap->values[index * 2 + 1]);
            new_index = index * 2 + 1;
        } else {
            to_compare = &(heap->values[index * 2 + 2]);
            new_index = index * 2 + 2;
        }
    }
    if (*to_compare < heap->values[index]) {
        swap_values(to_compare, &(heap->values[index]));
        heapify(heap, new_index);
    }
}

void heap_pop(binary_heap_t * const heap) {
    if (heap->length == 0) return;
    int *values = heap->values;
    values[0] = values[heap->length - 1];
    heap->length -= 1;
    heapify(heap, 0);
}