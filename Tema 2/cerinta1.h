#ifndef _CERINTA1_H_
#define _CERINTA1_H_

#include "tree.h"

void generate_tree_root(tree_t *tree_root, FILE *in);
void copy_cases(tree_t *tree_node, tree_t *copy_node);
int check_game_finished(tree_t *tree_node);
void build_tree(tree_t *tree_root, int to_play, short int empty_cases, int depth);
char n_to_c(int x);
void output_tree(tree_t *tree_root, FILE *out);
void read_from_file(tree_t *tree_root, FILE *in, int *first_play_as_num, short int *empty_cases);
void main_cerinta1(int argc, char *argv[]);
void set_truth(tree_t *tree_node, int our_player_num);
void output_cer2(tree_t *tree_node, FILE *out);
void main_cerinta2(int argc, char *argv[]);
void main_cerinta3(int argc, char *argv[]);

#endif