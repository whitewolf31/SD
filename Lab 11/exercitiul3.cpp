#include <algorithm>
#include <vector>
#include <math.h>

#include "dequeue.h"
#include "helpers.h"
#include "weighted_graph.h"
#include "node_weight.h"


std::vector<size_t> shortest_path(weighted_graph_t *graph, size_t source, size_t target) {
    std::vector<size_t> path;
    if (!graph || !valid_id(graph, source) || !valid_id(graph, target))
        return path;

    bool negative_cycle = false;
    bool *in_queue = (bool *)calloc(graph->node_count, sizeof(*in_queue));
    double *distance = (double *)calloc(graph->node_count, sizeof(*distance));
    size_t *parent = (size_t *)calloc(graph->node_count, sizeof(*parent));
    size_t *queue_apparitions = (size_t *)calloc(graph->node_count, sizeof(*queue_apparitions));
    dequeue_t *queue = alloc_deq();

    for (size_t i = 0; i < graph->node_count; i++) {
        distance[i] = INFINITY;
        parent[i] = i;
    }

    distance[source] = 0.0;
    push_back(queue, source);
    in_queue[source] = true;
    queue_apparitions[source] += 1;

    while(size(queue) > 0 && !negative_cycle) {
        size_t node_id = front(queue); pop_front(queue);
        in_queue[node_id] = false;

        if (distance[node_id] == INFINITY)
            continue;

        list_t *list = &graph->neighbours[node_id];
        FOR_LIST(iterator, list->sentinel->next, list->sentinel) {

            node_weight_t *nw = (node_weight_t *)iterator->info;

            size_t from_id = node_id;
            size_t to_id = nw->dest_node_idx;
            double weight = nw->weight;

            if (distance[to_id] > distance[from_id] + weight) {
                distance[to_id] = distance[from_id] + weight;
                parent[to_id] = from_id;
                if (!in_queue[to_id]) {
                    if (queue_apparitions[to_id] >= graph->node_count) {
                        negative_cycle = true;
                    } else {
                        push_back(queue, to_id);
                        in_queue[to_id] = true;
                        queue_apparitions[to_id] += 1;
                    }
                }
            }
        }
    }
    if (negative_cycle)
        return path;

    size_t iter = target;
    while(parent[iter] != iter) {
        path.push_back(iter);
        iter = parent[iter];
    }
    path.push_back(iter);

    if (path[path.size() - 1] == target){
        path.clear();
    }
    std::reverse(path.begin(), path.end());
    return path;
}
