#ifndef _LAB9_H_
#define _LAB9_H_
#define N 15

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t node_count;
    bool **adj_matrix;
} undirected_graph_t;

typedef struct node {
    size_t vertex;
    struct node *next;
    struct node *back;
} node_t;

typedef struct dequeue {
    node_t *front;
    node_t *back;
    size_t size;
} dequeue_t;

typedef void (*visit_func_t)(undirected_graph_t*, size_t vertex);

void graph_insert_edge(undirected_graph_t * const graph, const size_t vertex1, const size_t vertex2);
void graph_remove_edge(undirected_graph_t * const graph, const size_t vertex1, const size_t vertex2);
bool graph_is_edge(undirected_graph_t * const graph, const size_t vertex1, const size_t vertex2);
void graph_traverse_DFS_recursive(undirected_graph_t * const graph, bool * const visited, const size_t start_node_id, visit_func_t func);
void graph_traverse_DFS_iterative(undirected_graph_t * const graph, const size_t start_node_id, visit_func_t func);
void graph_traverse_BFS_iterative(undirected_graph_t * const graph, const size_t start_node_id, visit_func_t func);
void visit_node(undirected_graph_t * graph, size_t vertex);
int *shorest_path(undirected_graph_t * const graph, const size_t source_id, const size_t destination_id);
size_t connected_components(undirected_graph_t *graph);
bool check_if_in_dequeue(dequeue_t *dequeue, size_t vertex);
node_t * pop_queue(dequeue_t *dequeue);
void add_to_dequeue(dequeue_t *dequeue, node_t *node);

#endif