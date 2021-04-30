#ifndef __TRIE_NODE_H__
#define __TRIE_NODE_H__

#include <stdbool.h>

#define ALPHABET_SIZE 26
typedef struct trie_node {
    bool is_word_end;
    struct trie_node *children[ALPHABET_SIZE];
    struct trie_node *parent;
} trie_node_t;

trie_node_t init_trie_node(const bool is_word_end);
trie_node_t *alloc_trie_node(const bool is_word_end);
size_t ch_rank(const char ch);
void print_trie(const trie_node_t *root);

// exercitiul 2
void insert(trie_node_t *root, char *str);
void remove(trie_node_t *root, char *str);
bool contains(trie_node_t *root, char *str);
char **matchings(trie_node_t *root, char *str);

#endif
