#include "cerinte.h"

void set_truth(tree_t *tree_node, int our_player_num) {
    int truth = 0;
    if (tree_node->to_play != our_player_num) truth = 1;
    for (int i = 0; i < tree_node->children_length; i++) {
        set_truth(tree_node->children[i], our_player_num);
        if (tree_node->to_play != our_player_num) truth = truth && tree_node->children[i]->truth;
        else truth = truth || tree_node->children[i]->truth;
    }
    if (tree_node->children_length == 0) {
        if (tree_node->who_won == our_player_num) tree_node->truth = 1;
        else tree_node->truth = 0;
    } else tree_node->truth = truth;
}

void output_cer2(tree_t *tree_root, FILE *out) {
    if (tree_root == NULL) return;
    for (int k = 0; k < tree_root->depth; k++) fputc('\t', out);
    if (tree_root->truth == 1) fputs("T\n", out);
    else fputs("F\n", out);
    for (int i = 0; i < tree_root->children_length; i++) {
        output_cer2(tree_root->children[i], out);
    }
    if (tree_root->children != NULL) {
        free(tree_root->children);
    }
    free(tree_root);
}

void main_cerinta2(int argc, char *argv[]) {
    FILE *in, *out;
    in = fopen(argv[2], "r");
    out = fopen(argv[3], "w");
    tree_t *tree_root = (tree_t*) malloc(sizeof(tree_t));
    tree_root->depth = 0;
    int first_play_as_num;
    short int empty_cases;
    read_from_file(tree_root, in, &first_play_as_num, &empty_cases);
    build_tree(tree_root, first_play_as_num, empty_cases, 0);
    set_truth(tree_root, first_play_as_num);
    output_cer2(tree_root, out);
    fclose(in);
    fclose(out);
}