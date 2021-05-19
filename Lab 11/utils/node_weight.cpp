#include <stdlib.h>
#include "node_weight.h"

node_weight_t init_node_weight(size_t node_id, double weight) {
    node_weight_t nw = {
        .dest_node_idx = node_id,
        .weight = weight
    };
    return nw;
}

node_weight_t *alloc_node_weight(size_t node_id, double weight) {
    node_weight_t *nw = (node_weight_t *)calloc(1, sizeof(*nw));
    *nw = init_node_weight(node_id, weight);
    return nw;
}
