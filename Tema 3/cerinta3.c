#include "tema3.h"
#define MAX_INT 2147483647

int minimum(int a, int b) {
    if (a < b) return a;
    return b;
}

void DFSB(undirected_graph_t *graph, int v, int t, int *idx, int *low, int *pi, int *output_arr, int *index) {
    idx[v] = t;
    low[v] = t;
    t++;
    node_t *looper = graph->adjList[v]->first;
    while (looper != NULL) {
        int u = looper->value;
        if (u != pi[v]) {
            if (idx[u] == -1) {
                pi[u] = v;
                DFSB(graph, u, t, idx, low, pi, output_arr, index);
                low[v] = minimum(low[v], low[u]);
                if (low[u] > idx[v]) {
                    output_arr[*index] = v;
                    output_arr[*index + 1] = u;
                    *index += 2;
                }
            } else {
                low[v] = minimum(low[v], idx[u]);
            }
        }
        looper = looper->leg;
    }
}

void punti(undirected_graph_t *graph, int *output_arr, int *index) {
    int t = 0, i;
    int *idx = (int *) calloc(graph->num_of_nodes, sizeof(int));
    int *low = (int *) calloc(graph->num_of_nodes, sizeof(int));
    int *pi = (int *) calloc(graph->num_of_nodes, sizeof(int));
    for (i = 0; i < graph->num_of_nodes; i++) {
        idx[i] = -1;
        low[i] = MAX_INT;
        pi[i] = -1;
    }
    for (i = 0; i < graph->num_of_nodes; i++) {
        if (idx[i] == -1) {
            DFSB(graph, i, t, idx, low, pi, output_arr, index);
        }
    }
    free(idx);
    free(low);
    free(pi);
}

char **prepare_output(actor_t *actor_list, int *result_arr, int max_output) {
    int i;
    char **names_output_arr = (char **) malloc(max_output / 2 * sizeof(char *));
    for (i = 0; i < max_output / 2; i++) {
        names_output_arr[i] = (char *) malloc(100 * sizeof(char));
        char *first_str, *second_str;
        if (strcmp(actor_list[result_arr[2*i]].name, actor_list[result_arr[2*i + 1]].name) > 0) {
            first_str = actor_list[result_arr[2 * i + 1]].name;
            second_str = actor_list[result_arr[2 * i]].name;
        } else {
            first_str = actor_list[result_arr[2 * i]].name;
            second_str = actor_list[result_arr[2 * i + 1]].name;
        }
        strcpy(names_output_arr[i], first_str);
        strcat(names_output_arr[i], second_str);
        names_output_arr[i][strlen(first_str) - 1] = ' ';
    }
    qsort(names_output_arr, max_output / 2, sizeof(*names_output_arr), compare_function);
    return names_output_arr;
}

void output_cerinta3(FILE *out, char **names, int num_of_names) {
    int i;
    fprintf(out, "%d\n", num_of_names);
    for (i = 0; i < num_of_names; i++) {
        fprintf(out, "%s", names[i]);
    }
}

void main_cerinta3(FILE *in, FILE *out) {
    int i;
    size_t movie_number, actor_index = 0;
    fscanf(in, "%ld\n", &movie_number);
    actor_t *actor_list = (actor_t *) calloc(MAX_ACTOR_NUMBER, sizeof(actor_t));
    read_actors(in, actor_list, &actor_index, movie_number);
    undirected_graph_t *graph = generate_graph(actor_list, actor_index, movie_number);
    int *result_arr = (int *) calloc(200, sizeof(int));
    int max_output = 0;
    punti(graph, result_arr, &max_output);
    char **output_names = prepare_output(actor_list, result_arr, max_output);
    output_cerinta3(out, output_names, max_output / 2);
    // Dealocare memorie
    free(result_arr);
    for (i = 0; i < max_output/2; i++) free(output_names[i]);
    free(output_names);
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