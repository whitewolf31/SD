#ifndef __TEAM3_H__
#define __TEAM3_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LINE_CHAR 100
#define MAX_ACTOR_NUMBER 6000

typedef struct node {
    int value;
    struct node * leg;
} node_t;

typedef struct adj_list {
    node_t *first;
    node_t *last;
} adj_list_t;

typedef struct undirected_graph {
    int num_of_nodes;
    adj_list_t **adjList;
} undirected_graph_t;

typedef struct actor {
    bool movie_ids[200];
    char name[100];
} actor_t;

void main_cerinta1(FILE *in, FILE *out);
void main_cerinta2(FILE *in, FILE *out);
undirected_graph_t * init_graph(size_t n);
void add_edge(undirected_graph_t *graph, int src, int dest);
void read_actors(FILE *in, actor_t *actor_list, size_t *actor_index, size_t movie_number);
int check_actor_in_list(actor_t actor_list[], size_t actor_list_max, char actor_name[]);
undirected_graph_t *generate_graph(actor_t *actor_list, size_t actor_index, int max_movies);
void main_cerinta3(FILE *in, FILE *out);
int compare_function(const void *el1, const void *el2);

#endif