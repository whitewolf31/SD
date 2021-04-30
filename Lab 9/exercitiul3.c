#include "lab9.h"

int *shorest_path(undirected_graph_t * const graph, const size_t source_id, const size_t destination_id) {
    int * visited;
    visited = (int *) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) visited[i] = -1;
    dequeue_t *queue = (dequeue_t *) malloc(sizeof(dequeue_t));
    queue->back = NULL;
    queue->front = NULL;
    queue->size = 0;
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->back = NULL;
    new_node->vertex = source_id;
    add_to_dequeue(queue, new_node);
    visited[source_id] = source_id;
    while (queue->size != 0) {
        node_t *current_node = pop_queue(queue);
        for (int i = 0; i < 15; i++) {
            if (graph->adj_matrix[current_node->vertex][i] && visited[i] == -1 && !check_if_in_dequeue(queue, i)) {
                visited[i] = current_node->vertex;
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
    int v[N];
    int count = 0;
    int current = destination_id;
    while(current != source_id) {
        v[count++] = current;
        current = visited[current];
    }
    v[count] = source_id;
    int *return_arr = (int *) malloc((count + 2) * sizeof(int));
    for (int j = count; j >= 0; j--) return_arr[count - j] = v[j];
    return_arr[count + 1] = -1;
    return return_arr;
}