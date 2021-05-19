#include <stdio.h>
#include <math.h>

#include "node_weight.h"
#include "weighted_graph.h"

weighted_edge_t init_edge(size_t from, size_t to, double weight) {
    weighted_edge_t we = {
        .from = from,
        .to = to,
        .weight = weight
    };
    return we;
}

weighted_graph_t init_weighted_graph(size_t node_count) {
    weighted_graph_t graph = {
        .node_count = node_count,
        .neighbours = (list_t *)calloc(node_count, sizeof(list_t))
    };

    for (size_t i = 0; i < node_count; i++) {
        graph.neighbours[i] = *create_list();
    }
    return graph;
}

weighted_graph_t *alloc_weighted_graph(size_t node_count) {
    weighted_graph_t *graph = (weighted_graph_t *)malloc(sizeof(*graph));
    *graph = init_weighted_graph(node_count);
    return graph;
}

bool valid_id(weighted_graph_t *graph, size_t node_id) {
    if (!graph)
        return true;

    if (node_id >= graph->node_count)
        return false;

    return true;
}

weighted_graph_t *graph_load(const char *path) {

    FILE *fd = fopen(path, "r");
    if (!fd) {
        printf("[graph_load] [%s] not found.\n", path);
        return NULL;
    }

    size_t node_count = 0;
    size_t id, from, to;
    double weight;

    fscanf(fd, "%zd,from,to,weight\n", &node_count);
    weighted_graph_t *graph = alloc_weighted_graph(node_count);


    while(fscanf(fd, "%zd,%zd,%zd,%lf\n", &id, &from, &to, &weight) != EOF) {
        bool updated = false;
        list_t *list = &graph->neighbours[from];
        FOR_LIST(iterator, list->sentinel->next, list->sentinel) {
            node_weight_t *nw = (node_weight_t *)iterator->info;
            if (nw->dest_node_idx == to) {
                nw->weight = weight;
                updated = true;
                break;
            }
        }
        if (!updated)
            push_back(&graph->neighbours[from], alloc_node_weight(to, weight));

    }
    fclose(fd);

    return graph;
}

static size_t key_value = 0;
static double node_equals_values(void *n) {
    if (!n) {
        return 0;
    }
    node_t *node = (node_t *)n;
    node_weight_t *neighbour = (node_weight_t *)node->info;
    return neighbour->dest_node_idx == key_value;
}


double graph_get_weight(weighted_graph_t *graph, size_t from_id, size_t to_id) {

    if (!graph || !valid_id(graph, from_id) || !valid_id(graph, to_id))
        return INFINITY;

    key_value = to_id;
    node_t *destination_node = find_first(&graph->neighbours[from_id],
        node_equals_values);

    if (!destination_node)
        return INFINITY;

    node_weight_t *neighbour = (node_weight_t *)destination_node->info;

    return neighbour->weight;
}

void graph_insert_edge(weighted_graph_t *graph, size_t from_id, size_t to_id, double weight) {

    if (!graph || !valid_id(graph, from_id) || !valid_id(graph, to_id))
        return;

    graph_remove_edge(graph, from_id, to_id);
    push_back(&graph->neighbours[from_id], alloc_node_weight(to_id, weight));
}

void graph_insert_bidirectional_edge(weighted_graph_t *graph, size_t from_id, size_t to_id, double weight) {
    graph_insert_edge(graph, from_id, to_id, weight);
    graph_insert_edge(graph, to_id, from_id, weight);
}

void graph_remove_edge(weighted_graph_t *graph,
    size_t from_id,
    size_t to_id) {

    if (!graph || !valid_id(graph, from_id) || !valid_id(graph, to_id))
        return;

    key_value = to_id;
    node_t *to_node = find_first(&graph->neighbours[from_id], node_equals_values);
    remove_node(to_node);
}
