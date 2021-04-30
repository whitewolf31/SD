#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>

/*
 * Priority queue's most popular implementation called minimum heap. Priority
 * queues only define the functionality. It offers insert and peek minimum as
 * supported operations. The heap structure refers to how the aformentioned
 * structure is implemented.
 * Contains: vector of values, the capacity of the vector and size.
 */
typedef struct binary_heap {
    int *values;
    size_t capacity;
    size_t length;
} binary_heap_t;

/*
 * Allocates a min_heap_t structure on the stack.
 */
binary_heap_t init_heap(void);

/*
 * Allocates a binary_heap_t structure on heap. Useful when the heap outlives
 * the in function which it is created in.
 */
binary_heap_t *alloc_heap(void);

/*
 * Frees the memory of the internal buffer for the heap.
 */
void heap_free(binary_heap_t *heap);

/*
 * Check whether the heap is empty or not.
 */
bool heap_empty(binary_heap_t const * const heap);

/*
 * Prints the internal state of the heap. For debug purposes only.
 */
void heap_print(binary_heap_t const * const heap);

/*
 * Insertion operation on a dynamic array implementation of the heap.
 * @ heap  - the heap object
 * @ value - what to insert
 */
void heap_push(binary_heap_t * const heap, const int value);

/*
 * Inspects the minimum value stored in the heap.
 * @heap    - the heap object
 * @return  - o set the returned value on
 */
int heap_top(binary_heap_t const * const heap);

/*
 * Removes the minimum value stored in the heap.
 * @heap    - heap object
 */
void heap_pop(binary_heap_t * const heap);


/*
 * Removes the first occurence of a given value from the heap object.
 * @heap    - heap object
 * @value   - the value to be removed
 */
void heap_remove(binary_heap_t * const heap, const int value);

#endif
