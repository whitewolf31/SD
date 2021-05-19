#ifndef __LAB11_H__
#define __LAB11_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct weighted_graph {
    size_t node_count;
    double **adj_matrix;
} weighted_graph_t;

typedef struct {
    size_t from;
    size_t to;
    double weight;
} weighted_edge_t;

weighted_graph_t *init_graph(size_t node_count);
void graph_insert_bidirectional_edge(weighted_graph_t *graph, size_t from_id, size_t to_id, double weight);
double graph_get_weight(weighted_graph_t *graph, size_t from_id, size_t to_id);
void graph_insert_edge(weighted_graph_t *graph, size_t from_id, size_t to_id, double weight);
void graph_remove_edge(weighted_graph_t *graph, size_t from_id, size_t to_id);
weighted_edge_t *graph_get_all_edges(weighted_graph_t *graph);
double minimum_spanning_tree(weighted_graph_t *graph);

#endif