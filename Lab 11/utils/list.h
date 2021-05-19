#ifndef __LIST_H__
#define __LIST_H__

#include <time.h>

#define FOR_LIST(iter, begin, end) for (node_t *iter = (begin); iter != (end); iter = iter->next)

typedef struct node {
  void *info;
  struct node *next;
  struct node *prev;
} node_t;

node_t *alloc_node(void *info);
int link_after(node_t *prev, node_t *current);
int link_before(node_t *next, node_t *current);
void remove_node(node_t *node);


/*
 * Circular double linked list with sentinel.
 */
typedef struct list {
  node_t *sentinel;
  size_t length;
} list_t;

typedef double (*apply_func_t)(void *node);
list_t *create_list();

int push_front(list_t *list, void *info);
int push_back(list_t *list, void *info);
int pop_front(list_t *list);
int pop_back(list_t *list);
double aggregate(node_t *begin, node_t *end, apply_func_t func);
node_t *find_first(const list_t *list, apply_func_t func);


#endif
