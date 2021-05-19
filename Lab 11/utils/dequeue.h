#ifndef __DEQUEUE_H__
#define __DEQUEUE_H__

#include "list_node.h"

#define AS(TYPE, pointer) *(TYPE *)(pointer)

typedef struct {
  list_node_t *front;
  list_node_t *back;
  size_t length;
} dequeue_t;

dequeue_t init_deq();
dequeue_t *alloc_deq();

// acceseaza primul element
size_t front(dequeue_t *deq);

// acceseaza ultimul element
size_t back(dequeue_t *deq);

// insereaza un element in fata
void push_front(dequeue_t *deq, size_t value);

// insereaza un element in spate
void push_back(dequeue_t *deq, size_t value);

// scoate primul element
void pop_front(dequeue_t *deq);

// scoate ultimul element
void pop_back(dequeue_t *deq);

// intoarce numarul de elemente stocate in deq
size_t size(dequeue_t *deq);

void deq_print(dequeue_t *deq);

#endif
