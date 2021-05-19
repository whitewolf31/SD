#include <stdlib.h>
#include <numeric>
#include <math.h>

#include "scope_measurer.h"
#include "helpers.h"
#include "node_weight.h"
#include "weighted_graph.h"

static int exercise_id = 3.0;
std::vector<size_t> shortest_path(weighted_graph_t *graph,
    size_t source, size_t target);

static double path_cost(weighted_graph_t *graph, std::vector<size_t> path) {
    double path_cost = 0.0;

    if (path.size() <= 1)
        return 0.0;

    for (size_t i = 0; i < path.size() - 1; i++) {
        double weight = graph_get_weight(graph, path[i], path[i + 1]);

        if (weight == INFINITY)
            return INFINITY;
        path_cost += weight;
    }
    return path_cost;
}

static float test_shortest_path_simple() {
    const size_t test_count = 2;
    const float points = 5.0;
    std::vector<double> expected(test_count, points / test_count);
    std::vector<double> results(expected.size(), 0.0);

    weighted_graph_t *graph = graph_load("graphs/graph_v10_e10_nocycle.csv");
    std::vector<size_t> path;

    path = shortest_path(graph, 9, 5);
    results[0] = double_equals(path_cost(graph, path), 44.59);

    path = shortest_path(graph, 9, 1);
    results[1] = double_equals(path_cost(graph, path), 0.0);

    show_results(exercise_id + 0.1, "shortest path simple", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0)
        / results.size();
}

static float test_shortest_path_negative_weights() {
    const size_t test_count = 1;
    const float points = 1.0;
    std::vector<double> expected(test_count, points / test_count);
    std::vector<double> results(expected.size(), 0.0);

    std::vector<size_t> path;
    weighted_graph_t *graph = graph_load("graphs/graph_v4_e5.csv");

    path = shortest_path(graph, 0, 2);
    results[0] = double_equals(path_cost(graph, path), -200.60);

    show_results(exercise_id + 0.2, "shortest path negative weights", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0)
        / results.size();
}

static float test_shortest_path_negative_cycle() {
    const size_t test_count = 2;
    const float points = 1.0;
    std::vector<double> expected(test_count, points / test_count);
    std::vector<double> results(expected.size(), 0.0);

    std::vector<size_t> path;
    weighted_graph_t *graph = graph_load("graphs/graph_v10_e20.csv");

    path = shortest_path(graph, 5, 4);
    results[0] = double_equals(path_cost(graph, path), 0.0);

    path = shortest_path(graph, 5, 1);
    results[1] = double_equals(path_cost(graph, path), 0.0);

    show_results(exercise_id + 0.3, "shortest path negative cycle", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0)
        / results.size();
}

static float test_shortest_path_big_graphs() {
    const size_t test_count = 2;
    const float points = 1.0;
    std::vector<double> expected(test_count, points / test_count);
    std::vector<double> results(expected.size(), 0.0);

    std::vector<size_t> path;
    weighted_graph_t *graph = graph_load("graphs/graph_v100_e120.csv");
    path = shortest_path(graph, 3, 94);
    results[0] = double_equals(path_cost(graph, path), 56.80);

    graph = graph_load("graphs/graph_v10000_e10000.csv");
    path = shortest_path(graph, 0, 2669);
    results[1] = double_equals(path_cost(graph, path), 0.0);

    show_results(exercise_id + 0.4, "shortest path big graphs", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0)
        / results.size();
}

static float test_shortest_path_time() {
    const size_t test_count = 1;
    const float points = 1.0;
    std::vector<double> expected(test_count, points / test_count);
    std::vector<double> results(expected.size(), 0.0);

    std::vector<size_t> path;
    weighted_graph_t *graph;

    graph = graph_load("graphs/graph_v1500_e2000.csv");

    size_t query[][2] = {{3, 304}, {6, 385}, {6, 721}, {6, 1104}, {7, 370}, {10, 161},
        {10, 164}, {13, 161}, {13, 164}, {16, 1140}, {21, 183}, {21, 467}, {21, 481},
        {21, 482}, {21, 536}, {21, 569}, {21, 721}, {21, 724}, {21, 784}, {21, 961},
        {21, 999}, {21, 1055}, {21, 1103}, {21, 1104}, {21, 1140}, {21, 1271}, {21, 1454},
        {25, 722}, {25, 803}};

    double costs[] = {3.23, 16.55, 18.05, 22.38, -3.96, -1.39, 19.84, 1.95, 23.18,
        4.84, 49.88, 2.01, 35.02, -6.96, -18.41, -22.69, 3.70, -7.92, -8.64, 51.10, 14.15,
        0.53, -13.40, 8.03, 26.53, -2.35, -7.51, 4.46, 9.40};

    std::vector<size_t> largest_path;
    bool correct = true;

    ScopeMeasurer scope_measurer;

    scope_measurer.startMeasure();
    for (size_t i = 0; i < sizeof(query) / sizeof(query[0]); i++) {
        size_t source = query[i][0];
        size_t target = query[i][1];

        path = shortest_path(graph, source, target);
        correct = correct && double_equals(path_cost(graph, path), costs[i]);

        if (!correct)
            break;
    }
    scope_measurer.finishMeasure();
    results[0] = correct && scope_measurer.getTotalTime() <= 0.01;

    show_results(exercise_id + 0.5, "shortest path time", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0)
        / results.size();
}


float test_exercise3() {
    const size_t test_count = 5;
    const float points = 5.0;
    std::vector<double> expected(test_count, points / test_count);
    expected[0] = 5.0;
    std::vector<double> results(expected.size(), 0);

    results[0] = test_shortest_path_simple();
    results[1] = test_shortest_path_negative_weights();
    results[2] = test_shortest_path_negative_cycle();
    results[3] = test_shortest_path_big_graphs();
    results[4] = test_shortest_path_time();

    show_results(exercise_id, "shortest paths", expected, results);
    double total = 0;
    for (size_t idx = 0; idx < results.size(); idx ++) {
        total += results[idx] * expected[idx];
    }
    return total;
}
