#include "lab9.h"
#include <string.h>


int v[15];

void visit_node(undirected_graph_t * graph, size_t vertex) {
    static int count = 1;
    v[vertex] = count++;
}

int main(int argc, char *argv[]) {
    undirected_graph_t *graph = (undirected_graph_t *) malloc(sizeof(undirected_graph_t));
    graph->adj_matrix = (bool **) calloc(15, sizeof(bool*));
    for (int i = 0; i < 15; i++) {
        graph->adj_matrix[i] = (bool *) calloc(15, sizeof(bool));
    }

    // -----AICI SE ADAUGA NODURILE DIN GRAF
    graph_insert_edge(graph, 1, 2);
    graph_insert_edge(graph, 2, 6);
    graph_insert_edge(graph, 2, 7);
    graph_insert_edge(graph, 7, 6);
    graph_insert_edge(graph, 0, 7);
    graph_insert_edge(graph, 7, 8);
    graph_insert_edge(graph, 7, 3);
    graph_insert_edge(graph, 3, 4);
    graph_insert_edge(graph, 3, 5);
    graph_insert_edge(graph, 3, 10);
    graph_insert_edge(graph, 8, 9);
    graph_insert_edge(graph, 9, 12);
    graph_insert_edge(graph, 10, 12);
    graph_insert_edge(graph, 12, 11);
    graph_insert_edge(graph, 13, 11);
    graph_insert_edge(graph, 11, 14);
    graph_insert_edge(graph, 13, 14);


    if (strcmp(argv[1], "-c2") == 0) {
        printf("Alege mod parcurgere si nodul de start:\n1 pentru DFS Recursiv\n2 pentru DFS Iterativ\n3 pentru BFS Iterariv\nExemplu: 2 5 (Nodul mai mic ca 15)\n");
        int op1, op2;
        scanf("%d %d", &op1, &op2);
        if (op1 == 1) {
            printf("DFS Recursiv din nodul 3\n");
            bool * visited = (bool *) calloc(N, sizeof(bool));
            graph_traverse_DFS_recursive(graph, visited, op2, visit_node);
        } else if (op1 == 2) {
            printf("DFS Iterativ din nodul 3\n");
            graph_traverse_DFS_iterative(graph, op2, visit_node);
        } else if (op1 == 3) {
            printf("BFS Iterativ din nodul 3\n");
            graph_traverse_BFS_iterative(graph, op2, visit_node);
        } else {
            printf("Nu se cunoaste optiunea aleasa\n");
        }
        printf("INDEX NOD\n");
        for(int i = 0; i < N; i++) {
            if (i < 10) printf("%d  ", i);
            else printf("%d ", i);
        }
        printf("\n");
        printf("Mod Parcurgere\n");
        for (int i = 0; i < N; i++) {
            if (v[i] < 10) printf("%d  ", v[i]);
            else printf("%d ", v[i]);
        }
        printf("\n");
    } else if (strcmp(argv[1], "-c3") == 0) {
        printf("Cel mai mic drum intre nodul %s si nodul %s este:\n", argv[2], argv[3]);
        int *v_short = shorest_path(graph, atoi(argv[2]), atoi(argv[3]));
        int count = 0;
        while (v_short[count] != -1) {
            printf("%d ", v_short[count++]);
        }
        printf("%d ", v_short[count]);
        printf("\n");
    } else if (strcmp(argv[1], "-c4") == 0) {
        printf("Sunt %ld componente conex in acest graf\n", connected_components(graph));
    } else {
        printf("Nu se cunoaste comanda primita. Uita-te in README\n");
    }
    free(graph);
    return 0;
}