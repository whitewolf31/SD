#ifndef _LAB10_H_
#define _LAB10_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INT_MAX 2147483647

typedef struct weighted_graph {
    size_t node_count;
    double **adj_matrix;
} weighted_graph_t;

double graph_get_weight(weighted_graph_t *graph, size_t from_id, size_t to_id);
void graph_insert_edge(weighted_graph_t *graph, size_t from_id, size_t to_id, double weight);
void graph_remove_edge(weighted_graph_t *graph, size_t from_id, size_t to_id);
bool contains_cycle(weighted_graph_t *graph);
size_t *topological_sort(weighted_graph_t *graph);
size_t *shortest_path_bellman_ford(weighted_graph_t *graph, size_t source_id, size_t target_id);

weighted_graph_t *init_graph(size_t node_count);

#endif