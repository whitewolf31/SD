#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

#define HEAP_DEFAULT_CAPACITY 16

binary_heap_t init_heap(void) {
    binary_heap_t ret = {
        .values = (int *)malloc(HEAP_DEFAULT_CAPACITY * sizeof(int)),
        .capacity = HEAP_DEFAULT_CAPACITY,
        .length = 0,
    };
    return ret;
}

binary_heap_t *alloc_heap(void) {
    binary_heap_t *ret = (binary_heap_t *)malloc(sizeof(*ret));
    *ret = init_heap();
    return ret;
}

void heap_free(binary_heap_t *heap) {
    if (heap)
        free(heap->values);
    free(heap);
}

bool heap_empty(binary_heap_t const * const heap) {
    if (!heap)
        return true;
    return heap->length == 0;
}

void heap_print(binary_heap_t const * const heap) {
    if (heap_empty(heap)) {
        printf("(heap_null)");
        return;
    }
    printf("[#%3zd]", heap->length);
    for (size_t i = 0; i < heap->length; ++i) {
        printf("(%3zd:%3d)", i, heap->values[i]);
    }
}
