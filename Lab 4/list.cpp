#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include <stdlib.h>
#include <string.h>

void *memdup(const void* data, const size_t length) {
    void *data_copy = calloc(length, 1);
    memmove(data_copy, data, length);
    return data_copy;
}

node_t *new_node(const void *data, const size_t length) {
  node_t *node = (node_t *)calloc(1, sizeof(*node));
  node->data = memdup(data, length);
  node->length = length;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

void print_list(node_t *node) {
  int list_limit = 25;
  printf("[");
  for (node_t *iterator = node; iterator != NULL; iterator = iterator->next) {
      printf("%d", get_int_value(iterator));
      if (iterator->next)
          printf(", ");
      if (list_limit-- < 0) {
        break;
      }
  }
  printf("]\n");

  if (list_limit < 0) {
    printf("[Warning] the list was too long or there was a cycle?!\n");
  }
}

int get_int_value(const node_t *node) {
  if (!node) {
    return 0;
  }
  return *(int *)node->data;
}
