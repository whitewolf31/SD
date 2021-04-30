#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "trie.h"
#include "helpers.h"

typedef struct node {
  char *word;
  node *next;
} node_t;

void insert(trie_node_t *root, char *str) {
  for (size_t i = 0; i < strlen(str); i++) {
    if (root->children[str[i] - 'a'] == NULL) {
      trie_node_t *new_node = (trie_node_t *) malloc(sizeof(trie_node_t));
      if (i == strlen(str) - 1) new_node->is_word_end = 1;
      else new_node->is_word_end = 0;
      new_node->parent = root;
      root->children[str[i]- 'a'] = new_node;
    }
    root = root->children[str[i] - 'a'];
  }
  if (root->is_word_end != 1) root->is_word_end = 1;
}

bool contains(trie_node_t *root, char *str) {
  for (size_t i = 0; i < strlen(str); i++) {
    if (root->children[str[i] - 'a'] == NULL) return false;
    root = root->children[str[i] - 'a'];
  }
  if (root->is_word_end != 1) return false;
  return true;
}

bool check_siblings(trie_node_t *root, char x) {
  for (int i = 0; i < 26; i++) {
    if (i != x - 'a') {
      if (root->children[i] != NULL) return true;
    }
  }
  return false;
}

void remove(trie_node_t *root, char *str) {
  for (int i = 0; i < strlen(str); i++) {
    if (root->children[str[i] - 'a'] != NULL) {
      root = root->children[str[i] - 'a'];
    }
  } 
  root->is_word_end = 0;
  int j = strlen(str) - 1;
  while (1) {
    if (root->parent == NULL) break;
    if (root->is_word_end == 1) break;
    for (int i = 0; i < 26; i++) {
      if (root->children[i] != NULL) break;
    }
    trie_node_t *helper = root;
    root = root->parent;
    root->children[str[j] - 'a'] = NULL;
    free(helper);
    j--;
  }
}

void recursive_search(trie_node_t *root, node_t **list, char *word) {
  if (root->is_word_end == 1) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->word = word;
    new_node->next = NULL;
    if (*list == NULL) {
      *list = new_node;
    } else {
      node_t *looper = *list;
      while (looper->next != NULL) looper = looper->next;
      looper->next = new_node;
    } 
  }
  for (int i = 0; i < 26; i++) {
    if (root->children[i] != NULL) {
      char *new_word = (char *) malloc((strlen(word) + 2) * sizeof(char *));
      strcpy(new_word, word);
      char x = i + 'a';
      strncat(new_word, &x, 1);
      recursive_search(root->children[i], list, new_word);
    }
  }
}

char **matchings(trie_node_t *root, char *str) {
  for (int i = 0; i < strlen(str); i++) {
    if (root->children[str[i] - 'a'] == NULL) return NULL;
    root = root->children[str[i] - 'a'];
  }
  node_t *front = NULL;
  front = NULL;
  char *word = (char *) malloc((strlen(str) + 1) * sizeof(char));
  strcpy(word, str);
  recursive_search(root, &front, word);
  int size = 0;
  node_t *looper = front;
  while (looper != NULL) {
    looper = looper->next;
    size++;
  } 
  char** result = (char **) malloc((size + 1) * sizeof(char *));
  looper = front;
  int index = 0;
  while (looper != NULL) {
    result[index++] = looper->word;
    looper = looper->next;
  }
  result[index] = NULL; // Pt checker
  return result;
}
