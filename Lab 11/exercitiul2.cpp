#include <vector>
#include <stdio.h>

#include "list.h"
#include "node_weight.h"
#include "weighted_graph.h"


typedef struct {
    size_t count;
    size_t *group_id;
} disjoint_set_t;

disjoint_set_t init_disjoint_set(const size_t count) {
    disjoint_set_t r = {
        .count = count,
        .group_id = (size_t *)malloc(count * sizeof(size_t))
    };
    for (size_t i = 0; i < count; i++)
        r.group_id[i] = i;
    return r;
}

disjoint_set_t *alloc_disjoint_set(const size_t count) {
    disjoint_set_t *r = (disjoint_set_t *)malloc(sizeof(disjoint_set_t));
    *r = init_disjoint_set(count);
    return r;
}

bool ds_valid_id(disjoint_set_t *ds, const size_t id) {
    return ds && id < ds->count;
}

size_t ds_get_group_id(disjoint_set_t *ds, const size_t id) {
    if (!ds_valid_id(ds, id))
        return id;

    size_t iterator = id;
    while(iterator != ds->group_id[iterator])
        iterator = ds->group_id[iterator];

    return iterator;
}

void ds_merge(disjoint_set_t *ds, const size_t id1, const size_t id2) {
    if (!ds_valid_id(ds, id1) || !ds_valid_id(ds, id2))
        return;

    size_t g1 = ds_get_group_id(ds, id1);
    size_t g2 = ds_get_group_id(ds, id2);

    if (g1 != g2)
        ds->group_id[g1] = g2;
}

bool ds_same_group(disjoint_set_t *ds, const size_t id1, const size_t id2) {
    if (!ds_valid_id(ds, id1) || !ds_valid_id(ds, id2))
        return false;

    return ds_get_group_id(ds, id1) == ds_get_group_id(ds, id2);
}


typedef struct edge {
    size_t from;
    size_t to;
    double weight;
} edge_t;


int cmp_edges(const void *e1, const void *e2) {
    edge_t edge1 = *(edge_t *)e1;
    edge_t edge2 = *(edge_t *)e2;

    return edge1.weight - edge2.weight;
}

double minimum_spanning_tree(weighted_graph_t *graph) {
    size_t edge_count = 0;
    edge_t *edges = (edge_t *)malloc(graph->node_count * graph->node_count * sizeof(edge_t));
    disjoint_set_t *ds = alloc_disjoint_set(graph->node_count);
    double total_cost = 0.0f;

    for (size_t from = 0; from < graph->node_count; from++) {
        list_t *list = &graph->neighbours[from];
        FOR_LIST(iterator, list->sentinel->next, list->sentinel) {
            node_weight_t *nw = (node_weight_t *)iterator->info;
            edge_t e = {
                .from = from,
                .to = nw->dest_node_idx,
                .weight = nw->weight
            };
            edges[edge_count++] = e;
        }
    }

    qsort(edges, edge_count, sizeof(edge), cmp_edges);
    for (size_t i = 0; i < edge_count; i++)
        if (!ds_same_group(ds, edges[i].from, edges[i].to)) {
            total_cost += edges[i].weight;
            ds_merge(ds, edges[i].from, edges[i].to);
        }
    return total_cost;
}
