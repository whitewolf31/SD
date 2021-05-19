#include "lab11.h"

int main(int argc, char **argv) {
    weighted_graph_t *graph = init_graph(10);
    graph_insert_edge(graph, 4, 0, 1.92);
    graph_insert_edge(graph, 6, 5, 9.81);
    graph_insert_edge(graph, 3, 1, 1.35);
    graph_insert_edge(graph, 5, 1, 9.35);
    graph_insert_edge(graph, 3, 5, 0.76);
    graph_insert_edge(graph, 6, 8, 9.85);
    graph_insert_edge(graph, 8, 6, 10.17);
    graph_insert_edge(graph, 1, 4, 8.4);
    graph_insert_edge(graph, 1, 6, 10.47);
    graph_insert_edge(graph, 9, 3, 13.91);
    graph_insert_edge(graph, 4, 7, 2.14);
    graph_insert_edge(graph, 5, 3, 6.83);
    graph_insert_edge(graph, 0, 7, 2.19);
    graph_insert_edge(graph, 7, 2, 18.41);
    graph_insert_edge(graph, 2, 4, 4.31);
    graph_insert_edge(graph, 7, 9, 2.43);
    graph_insert_edge(graph, 8, 0, 7.97);
    graph_insert_edge(graph, 9, 8, 5.4);
    graph_insert_edge(graph, 0, 2, 4.49);
    
    weighted_edge_t *edges = graph_get_all_edges(graph);
    int index = 0;
    printf("EXERCITIUL 1-----------------\n");
    while (edges[index].from != -1) {
        printf("%ld %ld %.2lf\n", edges[index].from, edges[index].to, edges[index].weight);
        index++;
    }
    printf("\n");
    printf("EXERCITIUL 2-----------------\n");
    weighted_graph_t *graph2 = init_graph(6);
    graph_insert_bidirectional_edge(graph2, 0, 1, 1.0);
    graph_insert_bidirectional_edge(graph2, 0, 2, 2.0);
    graph_insert_bidirectional_edge(graph2, 1, 2, 17.0);
    graph_insert_bidirectional_edge(graph2, 3, 4, 2.0);
    graph_insert_bidirectional_edge(graph2, 3, 5, 2.0);
    graph_insert_bidirectional_edge(graph2, 4, 5, 3.0);
    double result = minimum_spanning_tree(graph2);
    printf("%.2lf\n", result);
    return 0;
}