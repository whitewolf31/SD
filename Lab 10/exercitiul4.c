#include "lab10.h"

size_t *shortest_path_bellman_ford(weighted_graph_t *graph, size_t source_id, size_t target_id) {
    double *distances = (double *) malloc(graph->node_count * sizeof(double));
    size_t *predecessors = (size_t *) malloc(graph->node_count * sizeof(size_t));
    for (int i = 0; i < graph->node_count; i++) predecessors[i] = -1;
    for (int i = 0; i < graph->node_count; i++) distances[i] = INT_MAX;
    distances[source_id] = graph->adj_matrix[source_id][source_id];
    for (int i = 1; i < graph->node_count; i++) {
        int changed = 0;
        for (int j = 0; j < graph->node_count; j++) {
            for (int k = 0; k < graph->node_count; k++) {
                if (graph->adj_matrix[j][k] != 0 && distances[k] > distances[j] + graph->adj_matrix[j][k]) {
                    distances[k] = distances[j] + graph->adj_matrix[j][k];
                    changed = 1;
                    predecessors[k] = j;
                }
            }
        }
        if (!changed) break;
    }
    size_t *path = (size_t *) malloc(graph->node_count * sizeof(size_t));
    for (int i = 0; i < graph->node_count; i++) path[i] = -1;
    size_t index = 0;
    size_t current = target_id;
    while (current != source_id) {
        path[index++] = predecessors[current];
        current = predecessors[current];
    }
    for (int i = 0; i < index / 2; i++) {
        size_t copy = path[i];
        path[i] = path[index - 1 - i];
        path[index - 1 - i] = copy;
    }
    path[index] = target_id;
    return path;
}