#include <stdio.h>

#include "tree.h"

void generate_tree_root(tree_t *tree_root, FILE *in) {
    // Se genereaza radacina arborelui, encodand 0 pentru -, 1 pt O si 2 pt X
    char looper_line[8];
    for (int i = 0; i < 3; i++) {
        fgets(looper_line, 8, in);
        for (int j = 0; j < 3; j++) {
            short int to_add;
            if (looper_line[2*j] == '-') to_add = 0;
            if (looper_line[2*j] == 'O') to_add = 1;
            if (looper_line[2*j] == 'X') to_add = 2; 
            tree_root->cases[i][j] = to_add;
        }
    }
}

void copy_cases(tree_t * tree_node, tree_t * copy_node) {
    // O functie ajutatoare pentru a copiat casutele unui nod din arbore in alt nod
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            copy_node->cases[i][j] = tree_node->cases[i][j];
        }
    }
}

int check_game_finished(tree_t *tree_node) {
    // Functia care verifica daca jocul s-a terminat
   int found = 0;
   // Se verifica pe coloane
   for (int i = 0; i < 3; i++) {
        found = found || (tree_node->cases[i][0] != 0 && tree_node->cases[i][0] == tree_node->cases[i][1] && tree_node->cases[i][0] == tree_node->cases[i][2]);
        if (found == 1) {
            tree_node->who_won = tree_node->cases[i][0];
            return found;
        }
   }
   // Se verifica pe linii
   for (int i = 0; i < 3; i++) {
        found = found || (tree_node->cases[0][i] != 0 && tree_node->cases[0][i] == tree_node->cases[1][i] && tree_node->cases[0][i] == tree_node->cases[2][i]);
        if (found == 1) {
            tree_node->who_won = tree_node->cases[0][i];
            return found;
        }
   }
   // Se verifica pe diagonale
   found = found || (tree_node->cases[0][0] != 0 && tree_node->cases[0][0] == tree_node->cases[1][1] && tree_node->cases[0][0] == tree_node->cases[2][2]);
   if (found == 1) {
        tree_node->who_won = tree_node->cases[0][0];
        return found;
    }
   found = found || (tree_node->cases[0][2] != 0 && tree_node->cases[0][2] == tree_node->cases[1][1] && tree_node->cases[0][2] == tree_node->cases[2][0]);
   if (found == 1) {
        tree_node->who_won= tree_node->cases[0][2];
        return found;
    }
    tree_node->who_won = 0;
    return found;
}

void build_tree(tree_t *tree_root, int to_play, short int empty_cases, int depth) {
    // Se construieste arborele de joc, pornind de la radacina
    if (empty_cases == 0) return;
    tree_root->children = (tree_t **) malloc(empty_cases * sizeof(tree_t*));
    int index = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tree_root->cases[i][j] == 0) {
                tree_t *new_node = (tree_t*) malloc(sizeof(tree_t));
                copy_cases(tree_root, new_node);
                new_node->depth = depth + 1;
                new_node->parent = tree_root;
                new_node->cases[i][j] = to_play;
                new_node->children_length = empty_cases - 1;
                new_node->children = NULL;
                int next_to_play = 1;
                if (to_play == 1) next_to_play = 2;
                new_node->to_play = next_to_play;
                tree_root->children[index++] = new_node;
                if (check_game_finished(new_node)) {
                    new_node->children_length = 0;
                } else {
                    build_tree(new_node, next_to_play, empty_cases - 1, depth + 1);
                }
            }
        }
    }
}

char n_to_c(int x) {
    // Functie ajutatoare de transformat din numar in caracter
    if (x == 0) return '-';
    if (x == 1) return 'O';
    else return 'X';
}

void output_tree(tree_t *tree_root, FILE *out) {
    // Functie pentru a afisa in fisier rezultatul, alaturi de tab-urile necesare
    if (tree_root == NULL) return;
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < tree_root->depth; k++) fputc('\t', out);
        for (int j = 0; j < 3; j++) {
            fputc(n_to_c(tree_root->cases[i][j]), out);
            if(j == 2) fputc('\n', out);
            else fputc(' ', out);
        }
    }
    fputc('\n', out);
    for (int i = 0; i < tree_root->children_length; i++) {
        output_tree(tree_root->children[i], out);
    }
    if (tree_root->children != NULL) {
        free(tree_root->children);
    }
    free(tree_root);
}

void read_from_file(tree_t *tree_root, FILE *in, int *first_play_as_num, short int *empty_cases) {
    // Se citeste din fisierul de input
    char first_line[10];
    fgets(first_line, 10, in);
    char first_play = first_line[0];
    generate_tree_root(tree_root, in);
    *empty_cases = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tree_root->cases[i][j] == 0) (*empty_cases)++;
        }
    }
    tree_root->children_length = (size_t) *empty_cases;
    tree_root->who_won = 0;
    *first_play_as_num = 2;
    if (first_play == 'O') *first_play_as_num = 1;
    tree_root->to_play = *first_play_as_num;
}

void main_cerinta1(int argc, char *argv[]) {
    FILE *in, *out;
    in = fopen(argv[2], "r");
    out = fopen(argv[3], "w");
    tree_t *tree_root = (tree_t*) malloc(sizeof(tree_t));
    tree_root->depth = 0;
    int first_play_as_num;
    short int empty_cases;
    read_from_file(tree_root, in, &first_play_as_num, &empty_cases);
    build_tree(tree_root, first_play_as_num, empty_cases, 0);
    output_tree(tree_root, out);
    fclose(in);
    fclose(out);
}