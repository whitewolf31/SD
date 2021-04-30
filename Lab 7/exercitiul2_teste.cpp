#include <iostream>
#include <numeric>
#include <stdlib.h>

#include "trie.h"
#include "helpers.h"

void print_trie(const trie_node_t *root);

static float test_trie_insert() {
  std::vector<double> expected(4, 3.0 / 4);
  std::vector<double> results(expected.size(), 0.0);

  trie_node_t *root = alloc_trie_node(false);
  insert(root, "ana");
  results[0] = (root
    && root
      ->children[ch_rank('a')]
    && !root
      ->children[ch_rank('a')]
      ->is_word_end
    && root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
    && !root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->is_word_end
    && root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
    && root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->is_word_end
  );

  insert(root, "ananas");
  results[1] = (root
    && root
      ->children[ch_rank('a')]
    && !root
      ->children[ch_rank('a')]
      ->is_word_end
    && root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
    && !root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->is_word_end
    && root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
    && root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->is_word_end
    && root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
    && !root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->is_word_end
    && root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
    && !root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->is_word_end
    && root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->children[ch_rank('s')]
    && root
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->children[ch_rank('n')]
      ->children[ch_rank('a')]
      ->children[ch_rank('s')]
      ->is_word_end
  );

  results[2] = (root && !root->children[ch_rank('b')]);
  insert(root, "bere");
  results[3] = (root
    && root
      ->children[ch_rank('b')]
    && !root
      ->children[ch_rank('b')]
      ->is_word_end
    && root
      ->children[ch_rank('b')]
      ->children[ch_rank('e')]
    && !root
      ->children[ch_rank('b')]
      ->children[ch_rank('e')]
      ->is_word_end
    && root
      ->children[ch_rank('b')]
      ->children[ch_rank('e')]
      ->children[ch_rank('r')]
    && !root
      ->children[ch_rank('b')]
      ->children[ch_rank('e')]
      ->children[ch_rank('r')]
      ->is_word_end
    && root
      ->children[ch_rank('b')]
      ->children[ch_rank('e')]
      ->children[ch_rank('r')]
      ->children[ch_rank('e')]
    && root
      ->children[ch_rank('b')]
      ->children[ch_rank('e')]
      ->children[ch_rank('r')]
      ->children[ch_rank('e')]
      ->is_word_end
  );

  show_results(2.1, "insert", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_trie_contains() {
  std::vector<double> expected(4, 2.0 / 4);
  std::vector<double> results(expected.size(), 0.0);

  trie_node_t *root = alloc_trie_node(false);

  results[0] = !contains(root, "ana");
  insert(root, "ana");
  results[1] = contains(root, "ana");

  insert(root, "ananas");
  results[2] = contains(root, "ananas");

  results[3] = !contains(root, "anana");

  show_results(2.2, "contains", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_trie_remove() {
  std::vector<double> expected(4, 3.0 / 4);
  std::vector<double> results(expected.size(), 0.0);

  trie_node_t *root = alloc_trie_node(false);
  results[0] = !contains(root, "ana");
  insert(root, "ana");
  results[1] = contains(root, "ana");
  remove(root, "ana");
  results[1] *= !contains(root, "ana");

  insert(root, "ananas");
  results[2] = contains(root, "ananas");
  remove(root, "ananas");
  results[2] *= !contains(root, "ananas");


  results[3] = !contains(root, "anana");
  remove(root, "anana");
  results[3] *= !contains(root, "anana");

  show_results(2.3, "remove", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_trie_matchings() {
  std::vector<double> expected(1, 2.0 / 1);
  std::vector<double> results(expected.size(), 0.0);

  trie_node_t *root = alloc_trie_node(false);
  insert(root, "analizat");
  insert(root, "anabela");
  insert(root, "ana");
  insert(root, "bere");
  insert(root, "anaerobic");
  insert(root, "analiza");
  insert(root, "anihilat");

  char **matches = matchings(root, "ana");
  const char *expected_matches[] = {
    "ana",
    "anabela",
    "anaerobic",
    "analiza",
    "analizat"
  };

  if (matches) {
    size_t expected_results_count = sizeof(expected_matches)
      / sizeof(expected_matches[0]);
    int idx = 0, idx_res = 0, ok = true;
    for(; idx < expected_results_count; idx++, idx_res++) {
      if (!matches[idx_res]) {
        ok = false;
        break;
      }
      ok &= !strcmp(matches[idx_res], expected_matches[idx]);
    }
    results[0] = ok && !matches[idx_res];
  }

  show_results(2.4, "matchings", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

float test_exercise2() {
  std::vector<double> expected = {3.0, 2.0, 3.0, 2.0};
  std::vector<double> results(expected.size(), 0);

  results[0] = test_trie_insert();
  results[1] = test_trie_contains();
  results[2] = test_trie_remove();
  results[3] = test_trie_matchings();

  show_results(2.0, "trie operations", expected, results);

  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
