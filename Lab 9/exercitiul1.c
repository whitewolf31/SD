#include "lab9.h"

void graph_insert_edge(undirected_graph_t * const graph, const size_t vertex1, const size_t vertex2) {
    graph->adj_matrix[vertex1][vertex2] = true;
    graph->adj_matrix[vertex2][vertex1] = true;
}

void graph_remove_edge(undirected_graph_t * const graph, const size_t vertex1, const size_t vertex2) {
    graph->adj_matrix[vertex1][vertex2] = false;
    graph->adj_matrix[vertex2][vertex1] = false;
}

bool graph_is_edge(undirected_graph_t * const graph, const size_t vertex1, const size_t vertex2) {
    return graph->adj_matrix[vertex1][vertex2];
}