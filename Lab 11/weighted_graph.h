#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <stdlib.h>

#include "list.h"
using namespace std;

typedef struct {
    size_t from;
    size_t to;
    double weight;
} weighted_edge_t;

weighted_edge_t init_edge(size_t, size_t, double);

typedef struct {
    size_t node_count;
    list_t *neighbours;
} weighted_graph_t;

weighted_graph_t init_weighted_graph(size_t);
weighted_graph_t *alloc_weighted_graph(size_t);
weighted_graph_t *graph_load(const char *);
void *graph_print(weighted_graph_t *);

bool valid_id(weighted_graph_t *, size_t);
double graph_get_weight(weighted_graph_t *, size_t, size_t);
void graph_insert_edge(weighted_graph_t *, size_t, size_t, double);
void graph_remove_edge(weighted_graph_t *, size_t, size_t);
void graph_insert_bidirectional_edge(weighted_graph_t *, size_t, size_t, double);

vector<weighted_edge_t> graph_get_all_edges(weighted_graph_t *);

#endif
