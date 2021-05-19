#include <algorithm>
#include <stdlib.h>
#include <numeric>
#include <vector>

#include "helpers.h"
#include "weighted_graph.h"

static int exercise_id = 2.0;

double minimum_spanning_tree(weighted_graph_t *graph);

static float test_mst_connex() {
    const size_t test_count = 1;
    const float points = 4.0;
    std::vector<double> expected(test_count, points / test_count);
    std::vector<double> results(expected.size(), 0.0);

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

    results[0] = minimum_spanning_tree(graph) == 14.0;
    show_results(exercise_id + 0.1, "1 group", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0)
        / results.size();
}

static float test_mst_forest() {
    const size_t test_count = 1;
    const float points = 5.0;
    std::vector<double> expected(test_count, points / test_count);
    std::vector<double> results(expected.size(), 0.0);

    weighted_graph_t *graph = alloc_weighted_graph(7);

    graph_insert_bidirectional_edge(graph, 0, 1, 1.0);
    graph_insert_bidirectional_edge(graph, 0, 2, 2.0);
    graph_insert_bidirectional_edge(graph, 1, 2, 17.0);
    graph_insert_bidirectional_edge(graph, 3, 4, 2.0);
    graph_insert_bidirectional_edge(graph, 3, 5, 2.0);
    graph_insert_bidirectional_edge(graph, 4, 5, 3.0);

    results[0] = minimum_spanning_tree(graph) == 7;

    show_results(exercise_id + 0.2, "forest", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0)
        / results.size();
}


float test_exercise2(void) {
    std::vector<double> expected = {4.0, 5.0};
    std::vector<double> results(expected.size(), 0);

    results[0] = test_mst_connex();
    results[1] = test_mst_forest();

    show_results(exercise_id, "minimum spanning tree", expected, results);
    double total = 0;
    for (size_t idx = 0; idx < results.size(); idx ++) {
        total += results[idx] * expected[idx];
    }
    return total;
}
