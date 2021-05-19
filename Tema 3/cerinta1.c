#include "tema3.h"

int check_actor_in_list(actor_t actor_list[], size_t actor_list_max, char actor_name[]) {
    int i;
    for (i = 0; i < actor_list_max; i++) {
        if (strcmp(actor_list[i].name, actor_name) == 0) return i;
    }
    return -1;
}

undirected_graph_t *generate_graph(actor_t *actor_list, size_t actor_index, int max_movies) {
    undirected_graph_t *graph = init_graph(actor_index);
    int i, j, k;
    for (i = 0; i < actor_index; i++) {
        for (j = i + 1; j < actor_index; j++) {
            for (k = 0; k < max_movies; k++) {
                if (actor_list[i].movie_ids[k] && actor_list[j].movie_ids[k]) {
                    add_edge(graph, i, j);
                }
            }
        }
    }
    return graph;
}

void DFS(undirected_graph_t *graph, int *visited, size_t current_node, int *sum, int conex_part) {
    (*sum)++;
    visited[current_node] = conex_part;
    node_t *looper = graph->adjList[current_node]->first;
    while(looper != NULL) {
        if (!visited[looper->value]) DFS(graph, visited, looper->value, sum, conex_part);
        looper = looper->leg;
    }
}

int check_if_unvisited(int *visited, size_t actor_index) {
    int i;
    for (i = 0; i < actor_index; i++) {
        if (visited[i] == 0) return i;
    }
    return -1;
}

int compare_function(const void *el1, const void *el2) {
    char **s1 = (char **) el1;
    char **s2 = (char **) el2;
    return strcmp(*s1, *s2);
}

void output(FILE *out, char **output_arr, int max_sum) {
    fprintf(out, "%d\n", max_sum);
    int i;
    for (i = 0; i < max_sum; i++) {
        fprintf(out, "%s", output_arr[i]);
    }
}

void read_actors(FILE *in, actor_t *actor_list, size_t *actor_index, size_t movie_number) {
    size_t movie_id_index = 0;
    int i, j;
    for (i = 0; i < movie_number; i++) {
        char buffer[MAX_LINE_CHAR];
        int actor_number;
        fgets(buffer, MAX_LINE_CHAR, in); // Numele filmului oricum nu conteaza sa il avem
        fscanf(in, "%d\n", &actor_number);
        for (j = 0; j < actor_number; j++) {
            fgets(buffer, MAX_LINE_CHAR, in);
            int found_id = check_actor_in_list(actor_list, *actor_index, buffer);
            if (found_id == -1) {
                strcpy(actor_list[*actor_index].name, buffer);
                actor_list[*actor_index].movie_ids[movie_id_index] = true;
                (*actor_index)++;
            } else {
                actor_list[found_id].movie_ids[movie_id_index] = true;
            }
        }
        movie_id_index++;
    }
}

void main_cerinta1(FILE *in, FILE *out) {
    size_t movie_number, actor_index = 0;
    fscanf(in, "%ld\n", &movie_number);
    int i;
    actor_t *actor_list = (actor_t *) calloc(MAX_ACTOR_NUMBER, sizeof(actor_t));
    read_actors(in, actor_list, &actor_index, movie_number);
    undirected_graph_t *graph = generate_graph(actor_list, actor_index, movie_number);
    int max_sum = 0;
    int current_conex_part = 1;
    int max_conex_part = 1;
    int *visited = (int *) calloc(actor_index, sizeof(int));
    int current_start = check_if_unvisited(visited, actor_index);
    while (current_start != -1) {
        int sum = 0;
        DFS(graph, visited, current_start, &sum, current_conex_part);
        if (sum > max_sum) {
            max_sum = sum;
            max_conex_part = current_conex_part;
        }
        current_conex_part++;
        current_start = check_if_unvisited(visited, actor_index);
    }
    char **output_arr = (char **) malloc(max_sum * sizeof(char *));
    int index = 0;
    for (i = 0; i < actor_index; i++) {
        if (visited[i] == max_conex_part) {
            output_arr[index] = (char *) malloc(50 * sizeof(char *));
            strcpy(output_arr[index++], actor_list[i].name);
        }
    }
    qsort(output_arr, max_sum, sizeof(*output_arr), compare_function);
    output(out, output_arr, max_sum);
    // Dealocare memorie
    free(visited);
    for (i = 0; i < max_sum; i++) free(output_arr[i]);
    free(output_arr);
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