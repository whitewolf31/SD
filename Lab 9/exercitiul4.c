#include "lab9.h"

int next_conex(bool *arr) {
    for (int i = 0; i < N; i++) {
        if (!arr[i]) return i;
    }
    return -1;
}

size_t connected_components(undirected_graph_t *graph) {
    bool *visited = (bool *) calloc(N, sizeof(bool));
    size_t nr = 0;
    while (1) {
        int next = next_conex(visited);
        if (next == -1) return nr;
        nr++;
        graph_traverse_DFS_recursive(graph, visited, next, visit_node);
    }
}