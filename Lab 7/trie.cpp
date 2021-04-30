#include <stdlib.h>
#include <stdio.h>

#include "trie.h"

size_t ch_rank(const char ch) {
  return ch - 'a';
}

trie_node_t init_trie_node(const bool is_word_end) {
    trie_node_t trie = {.is_word_end = is_word_end};
    return trie;
}

trie_node_t *alloc_trie_node(const bool is_word_end) {
    trie_node_t *trie = (trie_node_t *)calloc(1, sizeof(*trie));
    *trie = init_trie_node(is_word_end);
    return trie;
}

void print_trie_helper(
  const trie_node_t *root,
  int indent_lvl,
  bool print_arrow)
{
  if (!root) {
    printf("The root node should not be NULL, but somewhow it is\n");
    return;
  }

  bool has_children = false;
  bool is_first_chl = true;

  for (size_t idx = 0; idx < ALPHABET_SIZE; idx++) {
    if (!root->children[idx])
      continue;

    if (!is_first_chl)
      for (int i = 0; i < indent_lvl * 5 - 3; i++)
        printf(" ");

    if (is_first_chl)
      is_first_chl = false;

    if (print_arrow)
      printf("-> ");

    has_children = true;
    if (root->children[idx]->is_word_end)
      printf("%c]", (char)idx + 'a');
    else
      printf("%c ", (char)idx + 'a');

    print_trie_helper(root->children[idx], indent_lvl + 1, true);
  }
  if (!has_children) {
    printf("\n");
  }
}

void print_trie(const trie_node_t *root) {
  print_trie_helper(root, 0, false);
}
