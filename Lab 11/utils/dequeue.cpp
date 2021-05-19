#include "list_node.h"
#include "helpers.h"
#include "dequeue.h"

#define RETURN_VOID_IF_NULL(pointer) if (!(pointer)) { return; }
#define RETURN_IF_NULL(pointer, ret) if (!(pointer)) { return (ret); }

dequeue_t init_deq(void) {
  dequeue_t q = {
      .front = NULL,
      .back = NULL,
      .length = 0
  };
  return q;
}

dequeue_t *alloc_deq(void) {
  dequeue_t *q = (dequeue_t *)calloc(1, sizeof(*q));
  *q = init_deq();
  return q;
}

// acceseaza primul element
size_t front(dequeue_t *deq) {
  return AS(size_t, deq->front->data);
}

// acceseaza ultimul element
size_t back(dequeue_t *deq) {
  return AS(size_t, deq->back->data);
}

// insereaza un element in fata
void push_front(dequeue_t *deq, size_t value) {
  RETURN_VOID_IF_NULL(deq);
  list_node_t *node = new_node(&value, sizeof(value));
  RETURN_VOID_IF_NULL(node);

  push_front(deq->front, node);
  if (!deq->back)
    deq->back = deq->front;
  deq->length++;
}

// insereaza un element in spate
void push_back(dequeue_t *deq, size_t value) {
  RETURN_VOID_IF_NULL(deq);
  list_node_t *node = new_node(&value, sizeof(value));
  RETURN_VOID_IF_NULL(node);

  if (deq->back) {
    node->prev = deq->back;
    deq->back->next = node;
  }
  deq->back = node;

  if (!deq->front)
    deq->front = deq->back;
  deq->length++;
}

// scoate primul element
void pop_front(dequeue_t *deq) {
  RETURN_VOID_IF_NULL(deq);
  RETURN_VOID_IF_NULL(deq->front);
  list_node_t *to_free = deq->front;

  deq->front = deq->front->next;
  if (deq->front)
    deq->front->prev = NULL;
  else
    deq->back = NULL;
  free(to_free->data);
  free(to_free);
  deq->length--;
}

// scoate ultimul element
void pop_back(dequeue_t *deq) {
  RETURN_VOID_IF_NULL(deq);
  RETURN_VOID_IF_NULL(deq->back);
  list_node_t *to_free = deq->back;

  deq->back = deq->back->prev;
  if (deq->back)
    deq->back->next = NULL;
  else
    deq->front = NULL;

  free(to_free->data);
  free(to_free);
  deq->length--;
}

// intoarce numarul de elemente stocate in deq
size_t size(dequeue_t *deq) {
  RETURN_IF_NULL(deq, 0);
  RETURN_IF_NULL(deq->front, 0);
  return deq->length;
}

void deq_print(dequeue_t *deq) {
    RETURN_VOID_IF_NULL(deq);
    printf("[");
    for (list_node_t *iter = deq->front; iter; iter = iter->next) {
        printf("%2zd", AS(size_t, iter->data));
        if (iter != deq->back)
            printf(" ");
    }
    printf("]");
}
