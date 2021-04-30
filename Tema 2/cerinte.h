#ifndef _CERINTE_H_
#define _CERINTE_H_

#include "tree.h"

void build_tree(tree_t *tree_root, int to_play, short int empty_cases, int depth);
void read_from_file(tree_t *tree_root, FILE *in, int *first_play_as_num, short int *empty_cases);
void main_cerinta1(int argc, char *argv[]);
void main_cerinta2(int argc, char *argv[]);
void main_cerinta3(int argc, char *argv[]);

#endif