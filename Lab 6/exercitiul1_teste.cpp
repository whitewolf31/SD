#include <stdlib.h>
#include <numeric>

#include "bst_node.h"
#include "helpers.h"

#define TEST_CASE_VERBOSE 0
#define TEST_PARENT_LINK 0

static float test_insert() {
  std::vector<double> expected(6, 1.0 / 6.0);
  std::vector<double> results(expected.size(), 0.0);

  bst_node_t *root = NULL;
  insert(&root, 15.0);

  results[0] = (root
    && root->value == 15.0
    && !root->left
    && !root->right
    && (!TEST_PARENT_LINK || !root->parent)
  );
  insert(&root, 7.0);
  results[1] = (root
    && root->value == 15.0
    && root->left
    && !root->right
    && root->left->value == 7.0
    && !root->left->left
    && !root->left->right
    && (!TEST_PARENT_LINK
      || (!root->parent
      && root->left->parent == root))
  );

  insert(&root, 23.0);
  results[2] = (root
    && root->value == 15.0
    && root->left
    && root->right
    && root->left->value == 7.0
    && !root->left->left
    && !root->left->right
    && root->right->value == 23.0
    && !root->right->left
    && !root->right->right
    && (!TEST_PARENT_LINK
      || (!root->parent
      && root->left->parent == root
      && root->right->parent == root))
  );
  insert(&root, 20.0);
  insert(&root, 13.0);
    results[3] = (root
    && root->value == 15.0
    && root->left
    && root->right
    && root->left->value == 7.0
    && !root->left->left
    && root->left->right
    && root->right->value == 23.0
    && root->right->left
    && !root->right->right
    && (!TEST_PARENT_LINK
      || (!root->parent
      && root->left->parent == root
      && root->right->parent == root))
  );

  if (root) {
    bst_node_t *node7 = root->left;
    results[4] = (node7
      && node7->value == 7.0
      && !node7->left
      && node7->right
      && node7->right->value == 13.0
      && !node7->right->left
      && !node7->right->right
      && (!TEST_PARENT_LINK || (node7->parent == root
          && node7->right->parent == node7))
    );
    bst_node_t *node23 = root->right;
    results[5] = (node23
      && node23->value == 23.0
      && node23->left
      && !node23->right
      && node23->left->value == 20.0
      && !node23->left->left
      && !node23->left->right
      && (!TEST_PARENT_LINK
        || (node23->parent == root
          && node23->left->parent == node23))
    );
  }

  show_results(1.1, "insert", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}


static float test_search() {
  std::vector<double> expected(4, 1.0 / 4.0);
  std::vector<double> results(expected.size(), 0.0);

  bst_node_t *root = NULL;
  insert(&root, 15.0);
  bst_node_t *node0 = search(root, 23.0);
  results[0] = (root && !node0);
  insert(&root, 15.0);
  insert(&root, 23.0);
  insert(&root, 7.0);
  insert(&root, 13.0);
  insert(&root, 20.0);

  bst_node_t *node23 = search(root, 23.0);
  results[1] = (root && node23 && node23->value == 23.0);

  bst_node_t *node13 = search(root, 13.0);
  results[2] = (root && node13 && node13->value == 13.0);

  bst_node_t *node_not_found = search(root, 6546);
  results[3] = (root && !node_not_found);

  show_results(1.2, "search", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static float test_remove() {
  std::vector<double> expected(8, 3.0 / 8);
  std::vector<double> results(expected.size(), 0.0);

    // printf("Testul 7\n");

  bst_node_t *root1 = NULL;
  insert(&root1, 15.0);
  int insert_correct = (root1 != NULL);
  remove(&root1, 15.0);
  results[6] = (insert_correct && root1 == NULL);

  // printf("Testul 8\n");

  insert(&root1, 15.0);
  insert(&root1, 7.0);
  int parent7is15 = (root1
    && root1->left
    && (!TEST_PARENT_LINK || root1->left->parent == root1)
  );
  remove(&root1, 15.0);
  results[7] = (parent7is15
    && root1
    && root1->value == 7
    && (!TEST_PARENT_LINK || root1->parent == NULL)
  );
   // printf("Testul 1\n");
  bst_node_t *root = NULL;
  insert(&root, 15.0);
  insert(&root, 7.0);
  insert(&root, 23.0);
  insert(&root, 13.0);
  insert(&root, 20.0);
  insert(&root, 1.0);
  insert(&root, 27.0);
  if (TEST_CASE_VERBOSE) {
    print_tree(root);printf("\n");
  }
  remove(&root, 15.0);
  if (TEST_CASE_VERBOSE) {
    print_tree(root);printf("\n");
  }
  results[0] = (search(root, 15.0) == NULL
    && root
    && root->value == 20.0
    && root->right
    && !root->right->left
    && root->right->right
  );
    // printf("Testul 2\n");
  remove(&root, 7.0);
  if (TEST_CASE_VERBOSE) {
    print_tree(root);printf("\n");
  }
  results[1] = (search(root, 7.0) == NULL
    && root
    && root->value == 20.0
    && root->left
    && root->left->value == 13
    && root->left->left
    && !root->left->right
  );
    // printf("Testul 3\n");
  remove(&root, 1.0);
  if (TEST_CASE_VERBOSE) {
    print_tree(root);printf("\n");
  }
  results[2] = (search(root, 1.0) == NULL
    && root
    && root->value == 20.0
    && root->left
    && root->left->value == 13
    && !root->left->left
    && !root->left->right
  );

    // printf("Testul 4\n");

  int parent23is20 = (root
    && root->value == 20.0
    && root->right
    && root->right->value == 23.0);
  remove(&root, 20.0);
  if (TEST_CASE_VERBOSE) {
    print_tree(root);printf("\n");
  }
  results[3] = (search(root, 20.0) == NULL
    && root
    && root->value == 23.0
    && root->left
    && root->left->value == 13
    && root->right
    && root->right->value == 27
    && (!TEST_PARENT_LINK || (parent23is20 && !root->parent))
  );
    // printf("Testul 5\n");
  remove(&root, 20.0);
  if (TEST_CASE_VERBOSE) {
    print_tree(root);printf("\n");
  }
  results[4] = (search(root, 20.0) == NULL
    && root
    && root->value == 23.0
    && root->left
    && root->left->value == 13
    && root->right
    && root->right->value == 27
  );
    // printf("Testul 6\n");
  remove(&root, 23.0);
  remove(&root, 13.0);
  remove(&root, 27.0);
  if (TEST_CASE_VERBOSE) {
    print_tree(root);printf("\n");
  }
  results[5] = (insert_correct && root == NULL);
  show_results(1.3, "remove", expected, results);
  return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}


float test_exercise1() {
  std::vector<double> expected = {1.0, 1.0, 3.0};
  std::vector<double> results(expected.size(), 0);

  results[0] = test_insert();
  results[1] = test_search();
  results[2] = test_remove();

  show_results(1.0, "binary_search_tree", expected, results);
  double total = 0;
  for (size_t idx = 0; idx < results.size(); idx ++) {
    total += results[idx] * expected[idx];
  }
  return total;
}
