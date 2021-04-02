#ifndef __LIST_H__
#define __LIST_H__

typedef struct node {
  double data;
  struct node *next;
} node_t;

#define FOR(iterator, begin) for (node_t *iterator = (begin); iterator != NULL; iterator = iterator->next)
node_t *new_node(double data, node_t *next);
void print_list(node_t *node);

/*exercitiul1*/
void push_front(node_t **x, double data);
void push_back(node_t **x, double data);

/*exercitiul2*/
typedef double (*node_func_t)(const node_t *node);

void map(node_t *x, node_func_t func);
void filter(node_t **x, node_func_t func);
double aggregate(node_t *x, node_func_t func);

/*exercitiul3*/
node_t *intersection(node_t *n1, node_t *n2);

/*exercitiul4*/
void reverse(node_t **node);

/*exercitiul5*/
typedef int (*compare_t)(const void *e1, const void *e2);

void insert_sorted(node_t **node, double data, compare_t cmp);
node_t *merge_sorted(node_t **node1, node_t **node2, compare_t cmp);

/*exercitiul6*/
node_t *middle(node_t *node);
node_t *index(node_t* node, int index);

#endif
