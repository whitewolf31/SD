#include "lab10.h"

weighted_graph_t *init_graph(size_t node_count) {
    weighted_graph_t *new_graph = (weighted_graph_t *) malloc(sizeof(weighted_graph_t));
    new_graph->node_count = node_count;
    new_graph->adj_matrix = (double **) calloc(node_count, sizeof(double *));
    for (int i = 0; i < node_count; i++)
        new_graph->adj_matrix[i] = (double *) calloc(node_count, sizeof(double));
    return new_graph;
}

double graph_get_weight(weighted_graph_t *graph, size_t from_id, size_t to_id) {
    return graph->adj_matrix[from_id][to_id];
}

void graph_insert_edge(weighted_graph_t *graph, size_t from_id, size_t to_id, double weight) {
    graph->adj_matrix[from_id][to_id] = weight;
}

void graph_remove_edge(weighted_graph_t *graph, size_t from_id, size_t to_id) {
    graph->adj_matrix[from_id][to_id] = 0;
}