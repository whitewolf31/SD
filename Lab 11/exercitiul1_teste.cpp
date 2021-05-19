#include <stdlib.h>
#include <numeric>
#include <math.h>

#include "weighted_graph.h"
#include "helpers.h"

float test_exercise1(void) {
    std::vector<double> expected = {1.0};
    std::vector<double> results(expected.size(), 0);

    weighted_graph_t *graph = alloc_weighted_graph(8);
    graph_insert_bidirectional_edge(graph, 0, 1, 2.0);
    graph_insert_bidirectional_edge(graph, 0, 4, 4.0);
    graph_insert_bidirectional_edge(graph, 0, 5, 3.0);
    graph_insert_bidirectional_edge(graph, 0, 7, 15.0);
    graph_insert_bidirectional_edge(graph, 1, 2, 21.0);
    graph_insert_bidirectional_edge(graph, 1, 3, 19.0);
    graph_insert_bidirectional_edge(graph, 2, 3, 22.0);
    graph_insert_bidirectional_edge(graph, 2, 4, 3.0);
    graph_insert_bidirectional_edge(graph, 3, 4, 1.0);
    graph_insert_bidirectional_edge(graph, 4, 5, 4.0);
    graph_insert_bidirectional_edge(graph, 4, 6, 1.0);
    graph_insert_bidirectional_edge(graph, 5, 6, 17.0);
    graph_insert_bidirectional_edge(graph, 5, 7, 2.0);
    graph_insert_bidirectional_edge(graph, 6, 7, 2.0);

    vector<weighted_edge_t> edges = graph_get_all_edges(graph);
    results[0] = (edges.size() == 28);
    show_results(1.0, "get all edges", expected, results);
    double total = 0;
    for (size_t idx = 0; idx < results.size(); idx ++) {
        total += results[idx] * expected[idx];
    }
    return total;
}
