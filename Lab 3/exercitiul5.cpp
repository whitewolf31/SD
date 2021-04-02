#include <stdio.h>
#include <stdlib.h>

#include "list.h"


void insert_sorted(node_t **node, double data, compare_t cmp) {
  node_t *aux = *node;
  node_t *to_compare = (node_t *) malloc(sizeof(node_t));
  to_compare->data = data;
  to_compare->next = NULL;
  if (aux == NULL) {
    *node = to_compare;
    return;
  }
  if (cmp(aux, to_compare) < 0) {
    to_compare->next = aux;
    *node = to_compare;
    return;
  }
  while (aux->next != NULL) {
    if (cmp(aux->next, to_compare) < 0) {
      to_compare->next = aux->next;
      aux->next = to_compare;
      return;
    }
    aux = aux->next;
  }
  aux->next = to_compare;
}

node_t *merge_sorted(node_t **node1, node_t **node2, compare_t cmp) {
  node_t *aux2 = *node2;
  while (aux2 != NULL) {
    insert_sorted(node1, aux2->data, cmp);
    aux2 = aux2->next;
  }
  return *node1;
}
