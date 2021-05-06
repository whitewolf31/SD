#include "lab10.h"

void add_to_vector(size_t *vector, size_t max_size, size_t value) {
    for (int i = 0; i < max_size; i++) {
        if (vector[i] == max_size) {
            vector[i] = value;
            break;
        }
    }
}

void recursive_dfs(weighted_graph_t *graph, size_t current, int* visited, size_t *vector) {
    visited[current] = 1;
    for (int i = 0; i < graph->node_count; i++) {
        if (graph->adj_matrix[current][i] != 0 && visited[i] == 0) {
            recursive_dfs(graph, i, visited, vector);
        }
    }
    add_to_vector(vector, graph->node_count, current);
}

size_t *topological_sort(weighted_graph_t *graph) {
    if (contains_cycle(graph)) return NULL;
    int start;
    for (int i = 0; i < graph->node_count; i++) {
        int looper = 0;
        for (int j = 0; j < graph->node_count; j++) {
            looper = looper || graph->adj_matrix[j][i];
        }
        if (looper == 0) {
            start = i;
            break;
        }
    }
    int* visited = (int *) calloc(graph->node_count, sizeof(int));
    size_t *vector = (size_t *) malloc(graph->node_count * sizeof(size_t));
    for (int i = 0; i < graph->node_count; i++) vector[i] = graph->node_count;
    recursive_dfs(graph, start, visited, vector);
    return vector;
}