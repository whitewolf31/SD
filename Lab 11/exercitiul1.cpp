#include <math.h>
#include <stdio.h>

#include "weighted_graph.h"
#include "node_weight.h"

vector<weighted_edge_t> graph_get_all_edges(weighted_graph_t *graph) {
    vector<weighted_edge_t> edges;
    if (!graph)
        return edges;

    for (size_t from = 0; from < graph->node_count; from++) {
        list_t *list = &graph->neighbours[from];
        FOR_LIST(iterator, list->sentinel->next, list->sentinel) {
            node_weight_t *nw = (node_weight_t *)iterator->info;
            weighted_edge_t e = {
                .from = from,
                .to = nw->dest_node_idx,
                .weight = nw->weight
            };
            edges.push_back(e);
        }
    }
    return edges;
}
