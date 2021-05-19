#ifndef __NODE_WEIGHT_H__
#define __NODE_WEIGHT_H__

typedef struct node_weight {
    size_t dest_node_idx;
    double weight;
} node_weight_t;

node_weight_t init_node_weight(size_t, double);
node_weight_t *alloc_node_weight(size_t, double);

#endif
