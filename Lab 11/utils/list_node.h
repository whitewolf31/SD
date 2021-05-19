#ifndef __LIST_NODE_H__
#define __LIST_NODE_H__

#include <stdlib.h>

typedef struct lnode {
  void *data;
  size_t length;

  struct lnode *prev;
  struct lnode *next;
} list_node_t;

void *memdup(const void* data, const size_t length);
list_node_t *new_node(const void *data, const size_t length);
void print_list(list_node_t *node);

//exercise 1
void push_after(list_node_t *&current, list_node_t *new_node);
void push_front(list_node_t *&head, list_node_t *new_node);
void push_back(list_node_t *&head, list_node_t *new_node);

#endif
