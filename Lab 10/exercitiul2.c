#include "lab10.h"

int recursive_search(weighted_graph_t *graph, size_t *visited, size_t current) {
    int ret_val = 0;
    for (int i = 0; i < graph->node_count; i++) {
        if (graph->adj_matrix[current][i] != 0) {
            if (visited[i] == 1) return 1;
            if (visited[i] == 0) visited[i] = 1;
            ret_val = recursive_search(graph, visited, i);
        }
    }
    visited[current] = 2;
    return ret_val;
}

int check_if_all_visited(size_t *visited, size_t node_count) {
    for (int i = 0; i < node_count; i++) {
        if (visited[i] == 0) return i;
    }
    return -1;
}

bool contains_cycle(weighted_graph_t *graph) {
    size_t *visited = (size_t *) calloc(graph->node_count, sizeof(size_t));
    int current = 0;
    int ret_val = 0;
    while (current != -1) {
        ret_val = recursive_search(graph, visited, current);
        if (ret_val == 0) {
            current = check_if_all_visited(visited, graph->node_count);
        } else current = -1;
    }
    return ret_val;
}