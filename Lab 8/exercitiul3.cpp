#include "heap.h"
#include "helpers.h"

void heapify(binary_heap_t * const heap, const int index);

void heap_remove(binary_heap_t * const heap, const int value) {
    if (heap->length == 0) return;
    for (int i = 0; i < heap->length; i++) {
        if (heap->values[i] == value) {
            heap->values[i] = heap->values[heap->length - 1];
            heap->length -= 1;
            heapify(heap, i);
            break;
        }
    }
}
