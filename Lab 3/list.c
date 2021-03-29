#include <stdio.h>
#include <stdlib.h>

#include "list.h"

node_t *new_node(double data, node_t *next) {
  node_t *node = (node_t *)calloc(1, sizeof(*node));
  node->data = data;
  node->next = next;
  return node;
}

void print_list(node_t *node) {
  int list_limit = 100;
  printf("[");
  for (node_t *iterator = node; iterator != NULL; iterator = iterator->next) {
      printf("%lf", iterator->data);
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
