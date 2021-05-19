#include "tema3.h"

undirected_graph_t * init_graph(size_t n) { // Functie pentru a intializa graful cu un numar de n noduri
    undirected_graph_t *graph = (undirected_graph_t *) malloc(sizeof(undirected_graph_t));
    graph->num_of_nodes = n;
    graph->adjList = (adj_list_t **) malloc(n * sizeof(adj_list_t *));
    int i;
    for (i = 0; i < n; i++) { // Folosim liste de adiacenta
        graph->adjList[i] = (adj_list_t *) malloc(sizeof(adj_list_t));
        graph->adjList[i]->first = NULL;
        graph->adjList[i]->last = NULL;
    } 
    return graph;
}

node_t *create_node(int value) { // Functie pentru a crea un nod de legatura pentru lista de adiacenta
    node_t *node = (node_t *) malloc(sizeof(node_t));
    node->value = value;
    node->leg = NULL;
    return node;
}

void add_edge(undirected_graph_t *graph, int src, int dest) { // Functie pentru a adauga o muchie
    node_t *new_node_dest = create_node(dest);
    node_t *new_node_src = create_node(src);
    if (graph->adjList[src]->first == NULL) {
        graph->adjList[src]->first = new_node_dest;
        graph->adjList[src]->last = new_node_dest;
    } else {
        graph->adjList[src]->last->leg = new_node_dest;
        graph->adjList[src]->last = new_node_dest;
    }
    // Fiind graf neorientat trebuie sa adaugam in lista de adiacenta in ambele parti
    if (graph->adjList[dest]->first == NULL) {
        graph->adjList[dest]->first = new_node_src;
        graph->adjList[dest]->last = new_node_src;
    } else {
        graph->adjList[dest]->last->leg = new_node_src;
        graph->adjList[dest]->last = new_node_src;
    }
}