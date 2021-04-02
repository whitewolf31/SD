#include <stdio.h>
#include <stdlib.h>
#define ERROR_SUCCESS 0
#define ERROR_DEQUEUE_EMPTY -1


typedef struct node {
    double value;
    struct node* next;
    struct node* prev;
} node_t;

typedef struct {
    node_t *front;
    node_t *back;
    size_t size;
} dequeue_t;

dequeue_t *alloc_deq(void) {
    dequeue_t * queue = (dequeue_t *) malloc(sizeof(dequeue_t));
    queue->size = 0;
    queue->front = NULL;
    queue->back = NULL;
    return queue;
}

int front(dequeue_t *deq, double *value) {
    if (!deq || !deq->front || !value) {
        return ERROR_DEQUEUE_EMPTY;
    }
    *value = deq->front->value;
    return ERROR_SUCCESS;
}

int back(dequeue_t *deq, double *value) {
    if (!deq || !deq->back || !value) {
        return ERROR_DEQUEUE_EMPTY;
    }
    *value = deq->back->value;
    return ERROR_SUCCESS;
}

int push_front(dequeue_t *deq, double value) {
    if (!deq) {
        return ERROR_DEQUEUE_EMPTY;
    }
    node_t* new_node = (node_t *) malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    if (!deq->front) {
        deq->front = new_node;
        deq->back = new_node;
    } else {
        deq->front->prev = new_node;
        new_node->next = deq->front;
        deq->front = new_node;
    }
    deq->size++;
    return ERROR_SUCCESS;
}

int push_back(dequeue_t *deq, double value) {
    if (!deq) {
        return ERROR_DEQUEUE_EMPTY;
    }
    node_t* new_node = (node_t *) malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    if (!deq->back) {
        deq->front = new_node;
        deq->back = new_node;
    } else {
        deq->back->next = new_node;
        new_node->prev = deq->back;
        deq->back = new_node;
    }
    deq->size++;
    return ERROR_SUCCESS;
}

void pop_front(dequeue_t *deq) {
    if (!deq || !deq->front) return;
    node_t* first_node = deq->front;
    deq->front = deq->front->next;
    free(first_node);
    if (deq->size == 1) deq->back = NULL;
    deq->size--;
}

void pop_back(dequeue_t *deq) {
    if (!deq || !deq->back) return;
    node_t* last_node = deq->back;
    deq->back = deq->back->prev;
    free(last_node);
    if (deq->size == 1) deq->front = NULL;
    deq->size--;
}

size_t size(dequeue_t *deq) {
    return deq->size;
}