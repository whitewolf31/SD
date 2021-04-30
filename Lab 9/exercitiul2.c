#include "lab9.h"

void graph_traverse_DFS_recursive(undirected_graph_t * const graph, bool * const visited, const size_t start_node_id, visit_func_t func) {
    func(graph, start_node_id);
    if (!visited[start_node_id]) {
        visited[start_node_id] = true;
    };
    for (int i = 0; i < 15; i++) {
        if (i == start_node_id) continue;
        if (graph->adj_matrix[start_node_id][i] && !visited[i]) {
            visited[i] = true;
            graph_traverse_DFS_recursive(graph, visited, (size_t) i, func);
        }
    }
}

void add_to_dequeue(dequeue_t *dequeue, node_t *node) {
    if (dequeue->size == 0) {
        dequeue->back = node;
        dequeue->front = node;
    } else {
        node->next = dequeue->front;
        dequeue->front->back = node;
        dequeue->front = node;
    }
    dequeue->size++;
}

node_t * pop_queue(dequeue_t *dequeue) {
    if (dequeue->size == 0) return NULL;
    node_t *last_elem = dequeue->back;
    dequeue->back = dequeue->back->back;
    dequeue->size--;
    if (dequeue->size != 0) dequeue->back->next = NULL;
    return last_elem;
}

node_t *pop_stack(dequeue_t * dequeue) {
    if (dequeue->size == 0) return NULL;
    node_t *first_elem = dequeue->front;
    dequeue->front = dequeue->front->next;
    dequeue->size--;
    if (dequeue->size != 0) dequeue->front->back = NULL;
    return first_elem;
}

void remove_from_dequeue(dequeue_t *dequeue, size_t vertex) {
    node_t *remember = NULL;
    for (node_t *i = dequeue->front; i; i = i->next) {
        if (i->vertex == vertex) {
            if (i->next == NULL) dequeue->back = i->back;
            if (i->back == NULL) dequeue->front = i->next;
            remember = i;
            if (i->next != NULL) i->next->back = i->back;
            if (i->back != NULL) i->back->next = i->next;
            dequeue->size--;
            break;
        }
    }
    if (remember != NULL) free(remember);
}

bool check_if_in_dequeue(dequeue_t *dequeue, size_t vertex) {
    for (node_t *i = dequeue->front; i; i = i->next) {
        if (i->vertex == vertex) return true;
    }
    return false;
}

void graph_traverse_DFS_iterative(undirected_graph_t * const graph, const size_t start_node_id, visit_func_t func) {
    bool * visited;
    visited = (bool *) calloc(15, sizeof(bool));
    dequeue_t *stack = (dequeue_t *) malloc(sizeof(dequeue_t));
    stack->back = NULL;
    stack->front = NULL;
    stack->size = 0;
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->back = NULL;
    new_node->vertex = start_node_id;
    add_to_dequeue(stack, new_node);
    while (stack->size != 0) {
        node_t *current_node = pop_stack(stack);
        func(graph, current_node->vertex);
        visited[current_node->vertex] = true;
        visited[current_node->vertex] = true;
        for (int i = 14; i >= 0; i--) {
            if (graph->adj_matrix[current_node->vertex][i] && !visited[i]) {
                remove_from_dequeue(stack, i);
                new_node = (node_t *) malloc(sizeof(node_t));
                new_node->next = NULL;
                new_node->back = NULL;
                new_node->vertex = i;
                add_to_dequeue(stack, new_node);
            }
        }
        free(current_node);
    }
    free(stack);
}

void graph_traverse_BFS_iterative(undirected_graph_t * const graph, const size_t start_node_id, visit_func_t func) {
    bool * visited;
    visited = (bool *) calloc(15, sizeof(bool));
    dequeue_t *queue = (dequeue_t *) malloc(sizeof(dequeue_t));
    queue->back = NULL;
    queue->front = NULL;
    queue->size = 0;
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->back = NULL;
    new_node->vertex = start_node_id;
    add_to_dequeue(queue, new_node);
    visited[start_node_id] = true;
    while (queue->size != 0) {
        node_t *current_node = pop_queue(queue);
        func(graph, current_node->vertex);
        for (int i = 0; i < 15; i++) {
            if (graph->adj_matrix[current_node->vertex][i] && !visited[i] && !check_if_in_dequeue(queue, i)) {
                visited[i] = true;
                new_node = (node_t *) malloc(sizeof(node_t));
                new_node->next = NULL;
                new_node->back = NULL;
                new_node->vertex = i;
                add_to_dequeue(queue, new_node);
            }
        }
        free(current_node);
    }
    free(queue);
}