#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR_SUCCESS 0
#define ERROR_DEQUEUE_EMPTY -1

typedef struct node {
    int value;
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

int front(dequeue_t *deq, int *value) {
    if (!deq || !deq->front || !value) {
        return ERROR_DEQUEUE_EMPTY;
    }
    *value = deq->front->value;
    return ERROR_SUCCESS;
}

int back(dequeue_t *deq, int *value) {
    if (!deq || !deq->back || !value) {
        return ERROR_DEQUEUE_EMPTY;
    }
    *value = deq->back->value;
    return ERROR_SUCCESS;
}

int push_front(dequeue_t *deq, int value) {
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

int push_back(dequeue_t *deq, int value) {
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

int get_kth_digit(const int number, const int kth) {
    int num_copy = number;
    int k_digit = kth;
    while (k_digit > 1) {
        num_copy /= 10;
        k_digit--;
    }
    return num_copy % 10;
}

int radix_sort(int vec[], const size_t length) {
    dequeue_t * queue_array[10];
    for (int i = 0; i < 10; i++) {
        queue_array[i] = alloc_deq();
    }
    for (int i = 1; i <= 12; i++) {
        for (int j = 0; j < length; j++) {
            int digit = get_kth_digit(vec[j], i);
            push_front(queue_array[digit], vec[j]);
        }
        int index = 0;
        for (int j = 0; j < 10; j++) {
            int currentValue;
            while (size(queue_array[j]) > 0) {
                back(queue_array[j], &currentValue);
                pop_back(queue_array[j]);
                vec[index++] = currentValue;
            }
        }
    }
    return ERROR_SUCCESS;
}

int main(int argc, char *argv[]) {
    int v[10] = {329, 12, 9, 457, 657, 839, 436, 1000, 720, 355};
    radix_sort(v, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    return 0;
}