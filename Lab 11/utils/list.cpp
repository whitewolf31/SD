#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define RETURN_VOID_IF_NULL(pointer) if (!(pointer)) { return; }
#define RETURN_IF_NULL(pointer, ret) if (!(pointer)) { return (ret); }

node_t *alloc_node(void *info) {
  node_t *node = (node_t *)calloc(1, sizeof(*node));
  node->info = info;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

int link_after(node_t *prev, node_t *current) {
  RETURN_IF_NULL(prev, -1);
  RETURN_IF_NULL(current, -1);

  if (current->next || current->prev) {
    printf("Warning [link after] current is already linked to other nodes\n");
  }

  current->next = prev->next;
  prev->next->prev = current;

  prev->next = current;
  current->prev = prev;

  return 0;
}

int link_before(node_t *next, node_t *current) {
  RETURN_IF_NULL(next, -1);
  RETURN_IF_NULL(current, -1);
  return link_after(next->prev, current);
}

void remove_node(node_t *node) {
  RETURN_VOID_IF_NULL(node);

  node_t *curr = node;
  curr->prev->next = curr->next;
  curr->next->prev = curr->prev;

  curr->next = NULL;
  curr->prev = NULL;

  if (curr->info)
    free(curr->info);
  free(curr);
}

list_t *create_list() {
  list_t *list = (list_t *)calloc(1, sizeof(*list));
  list->sentinel = alloc_node(NULL);
  list->sentinel->next = list->sentinel;
  list->sentinel->prev = list->sentinel;
  list->length = 0;
  return list;
}

int push_front(list_t *list, void *info) {
  RETURN_IF_NULL(list, -1);
  RETURN_IF_NULL(info, -1);

  list->length += 1;
  node_t *node = alloc_node(info);
  return link_after(list->sentinel, node);
}

int push_back(list_t *list, void *info) {
  RETURN_IF_NULL(list, -1);
  RETURN_IF_NULL(info, -1);

  list->length += 1;
  node_t *node = alloc_node(info);
  return link_before(list->sentinel, node);
}

int static empty_list(const list_t *list) {
  RETURN_IF_NULL(list, 1);
  return list->sentinel->next == list->sentinel && list->sentinel->prev == list->sentinel;
}

int pop_front(list_t *list) {
  if (empty_list(list)) {
    return -1;
  }
  list->length -= 1;
  remove_node(list->sentinel->next);
  return 0;
}

int pop_back(list_t *list) {
  if (empty_list(list)) {
    return -1;
  }
  list->length -= 1;
  remove_node(list->sentinel->prev);
  return 0;
}

node_t *find_first(const list_t *list, apply_func_t apply_func) {
  RETURN_IF_NULL(list, NULL);
  RETURN_IF_NULL(apply_func, NULL);

  FOR_LIST(iterator, list->sentinel->next, list->sentinel) {
    if (apply_func(iterator) == 1.0) {
      return iterator;
    }
  }
  return NULL;
}


double aggregate(node_t *begin, node_t *end, apply_func_t func) {
  RETURN_IF_NULL(begin, -1);
  RETURN_IF_NULL(end, -1);
  RETURN_IF_NULL(func, -1);

  double aggreg_res = 0;
  int limit = 100000;

  FOR_LIST(iterator, begin, end) {
    aggreg_res += func(iterator);
    if (limit-- <= 0)
      break;
  }
  return aggreg_res;
}
