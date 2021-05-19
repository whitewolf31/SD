#include "lab11.h"

int compare_function (const void * el1, const void * el2) {
    weighted_edge_t *edge1 = (weighted_edge_t *) el1;
    weighted_edge_t *edge2 = (weighted_edge_t *) el2;
    double difference = edge1->weight - edge2->weight;
    if (difference > 0) return 1;
    else return -1;
}

size_t find(size_t node, size_t *group) {
    if (group[node] == node) return node;
    else return find(group[node], group);
}

weighted_edge_t *graph_get_all_bideractional_edges(weighted_graph_t *graph) {
    weighted_edge_t *edges = (weighted_edge_t *) malloc(graph->node_count * (graph->node_count - 1) * sizeof(weighted_edge_t)); // Nu e nevoie de eficienta in memorie deocamdata
    int index = 0;
    for (int i = 0; i < graph->node_count; i++) {
        for (int j = i; j < graph->node_count; j++) {
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

double minimum_spanning_tree(weighted_graph_t *graph) {
    weighted_edge_t *edges = graph_get_all_bideractional_edges(graph);
    int num_of_edges = 0;
    while (edges[num_of_edges].from != -1) num_of_edges++;
    qsort(edges, num_of_edges, sizeof(weighted_edge_t), compare_function);
    size_t *group = (size_t *) malloc(num_of_edges * sizeof(size_t));
    for (int i = 0; i < num_of_edges; i++) group[i] = i;
    double sum = 0;
    for (int i = 0; i < num_of_edges; i++) {
        int g1 = find(edges[i].from, group);
        int g2 = find(edges[i].to, group);
        if (g1 != g2) {
            sum += edges[i].weight;
            group[g2] = g1;
        }
    }
    return sum;
}