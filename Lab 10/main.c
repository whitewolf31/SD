#include "lab10.h"

int main(int argc, char **argv) {
    // Exercitiul 1
    weighted_graph_t *graph = init_graph(10);
    graph_insert_edge(graph, 0, 1, 2.5);
    graph_insert_edge(graph, 1, 4, 3.5);
    graph_insert_edge(graph, 4, 3, 1);
    graph_insert_edge(graph, 2, 3, 1.5);
    graph_insert_edge(graph, 4, 5, 5.5);
    graph_insert_edge(graph, 5, 2, 3.3);
    graph_insert_edge(graph, 5, 7, 2);
    graph_insert_edge(graph, 4, 6, 5.5);
    graph_insert_edge(graph, 7, 6, 3.1);
    graph_insert_edge(graph, 6, 8, 2.5);
    graph_insert_edge(graph, 8, 9, 1);
    graph_insert_edge(graph, 9, 2, 0.2);
    // Exercitiul 2
    printf("%d\n", contains_cycle(graph));
    // Exercitiul 3
    size_t *vector = topological_sort(graph);
    for (int i = 0; i < graph->node_count; i++) printf("%ld ", vector[i]);
    printf("\n");
    // Exercitiul 4
    size_t *vector2 = shortest_path_bellman_ford(graph, 6, 2);
    for (int i = 0; i < graph->node_count && vector2[i] != -1; i++) {
        printf("%ld ", vector2[i]);
    }
    printf("\n");
    return 0;
}