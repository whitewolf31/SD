#include "tema3.h"


typedef struct queue_node{
    int value;
    struct queue_node * next;
    struct queue_node * prev;
} queue_node_t;

typedef struct queue {
    size_t size;
    queue_node_t *first;
    queue_node_t *last;
} queue_t;

queue_t *init_queue() {
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
    queue->size = 0;
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}

queue_node_t *generate_queue_node(int value) {
    queue_node_t *new_node = (queue_node_t *) malloc(sizeof(queue_node_t));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void add_to_queue(queue_t *queue, int value) {
    queue_node_t *new_node = generate_queue_node(value);
    if (queue->size == 0) {
        queue->first = new_node;
        queue->last = new_node;
    } else {
        queue->first->prev = new_node;
        new_node->next = queue->first;
        queue->first = new_node;
    }
    queue->size++;
}

int pop_from_queue(queue_t *queue) {
    if (queue->size == 0) return -1;
    int value = queue->last->value;
    queue_node_t *current = queue->last;
    if (queue->size == 1) {
        queue->last = NULL;
        queue->first = NULL;
    } else {
        queue->last = queue->last->prev;
        queue->last->next = NULL;
    }
    free(current);
    queue->size--;
    return value;
}

void BFS(undirected_graph_t *graph, int *visited, int src, int dest) {
    visited[src] = 1;
    queue_t *queue = init_queue();
    add_to_queue(queue, src);
    while (queue->size != 0) {
        int current_node = pop_from_queue(queue);
        node_t *looper = graph->adjList[current_node]->first;
        while(looper != NULL) {
            if (visited[looper->value] == 0) {
                visited[looper->value] = visited[current_node] + 1;
                add_to_queue(queue, looper->value);
            }
            looper = looper->leg;
        }
    }
    free(queue);
}

void main_cerinta2(FILE *in, FILE *out) {
    int i;
    size_t movie_number, actor_index = 0;
    fscanf(in, "%ld\n", &movie_number);
    actor_t *actor_list = (actor_t *) calloc(MAX_ACTOR_NUMBER, sizeof(actor_t));
    read_actors(in, actor_list, &actor_index, movie_number);
    undirected_graph_t *graph = generate_graph(actor_list, actor_index, movie_number);
    int *visited = (int *) calloc(actor_index, sizeof(int));
    char buffer[MAX_LINE_CHAR];
    fgets(buffer, MAX_LINE_CHAR, in); // Getting source node
    int found_id_src = check_actor_in_list(actor_list, actor_index, buffer);
    fgets(buffer, MAX_LINE_CHAR, in); // Getting destination node
    int found_id_dest = check_actor_in_list(actor_list, actor_index, buffer);
    if (found_id_src == -1 || found_id_dest == -1) {
        fprintf(out, "%d\n", -1);
    } else {
        BFS(graph, visited, found_id_src, found_id_dest);
        if (visited[found_id_dest] == 0) {
            fprintf(out, "%d\n", -1);
        } else {
            fprintf(out, "%d\n", visited[found_id_dest] - 1);
        }
    }
    // Dealocare memorie
    free(visited);
    for (i = 0; i < graph->num_of_nodes; i++) {
        node_t *looper = graph->adjList[i]->first;
        while(looper != NULL) {
            node_t *freer = looper;
            looper = looper->leg;
            free(freer);
        }
        free(graph->adjList[i]);
    }
    free(actor_list);
    free(graph->adjList);
    free(graph);
}