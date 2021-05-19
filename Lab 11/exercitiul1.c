#include "lab11.h"

weighted_edge_t *graph_get_all_edges(weighted_graph_t *graph) {
    weighted_edge_t *edges = (weighted_edge_t *) malloc(graph->node_count * (graph->node_count - 1) * sizeof(weighted_edge_t)); // Nu e nevoie de eficienta in memorie deocamdata
    int index = 0;
    for (int i = 0; i < graph->node_count; i++) {
        for (int j = 0; j < graph->node_count; j++) {
            if (graph->adj_matrix[i][j] != 0) {
                edges[index].from = i;
                edges[index].to = j;
                edges[index].weight = graph->adj_matrix[i][j];
                index++;
            }
        }
    }
    edges[index].from = -1;
    return edges;
}