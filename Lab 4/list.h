#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

typedef struct node {
  void *data;
  size_t length;

  struct node *prev;
  struct node *next;
} node_t;

enum direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

void *memdup(const void* data, const size_t length);
node_t *new_node(const void *data, const size_t length);
void print_list(node_t *node);
int get_int_value(const node_t *node);

//exercise 1
void push_after(node_t *&current, node_t *new_node);
void push_front(node_t *&head, node_t *new_node);
void push_back(node_t *&head, node_t *new_node);

// exercise 2
void remove(node_t *&node);
node_t *nth_element(node_t *const head, const size_t nth);

// exercitiul3
typedef int (*node_func_t)(node_t const* node);
void apply(node_t *begin, node_t *end, node_func_t func);

// exercitiul4
size_t remove_equal_sequence(node_t *&begin, node_t *end, node_func_t func);

//exercitiul5
void swap_with_neighbour(node_t *current, node_t *left,
                        node_t *up, node_t *right,
                        node_t *down, enum direction dir);

//exercitiul6
void insert_circular(node_t **head, node_t *node);
#endif
