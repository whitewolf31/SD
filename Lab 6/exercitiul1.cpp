#include "helpers.h"
#include "bst_node.h"

bst_node_t *getSuccessor(bst_node_t *right) {
  if (right->left == NULL) return right;
  else return getSuccessor(right->left);
}

void insert(bst_node_t **root_ptr, const double value) {
  bst_node_t *new_node = (bst_node_t *) malloc(sizeof(bst_node_t));
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->parent = NULL;
  if (*root_ptr == NULL) {
    *root_ptr = new_node;
    return;
  }
  bst_node_t *looper = *root_ptr;
  while (1) {
    if (value > looper->value) {
      if (looper->right == NULL) {
        looper->right = new_node;
        new_node->parent = looper;
        break;
      } else looper = looper->right;
    } else {
      if (looper->left == NULL) {
        looper->left = new_node;
        new_node->parent = looper;
        break;
      } else looper = looper->left;
    }
  }
}

bst_node_t *search(bst_node_t * const root, const double value) {
  if (root == NULL) return NULL;
  if (root->value == value) return root;
  if (root->value < value) return search(root->right, value);
  return search(root->left, value);
}

void display_tree(bst_node_t *root_ptr) {
  if (root_ptr == NULL) return;
  printf("%lf ", root_ptr->value);
  display_tree(root_ptr->left);
  display_tree(root_ptr->right);
}

void remove(bst_node_t **root_ptr, const double value) {
 // printf("---------\n");
  //display_tree(*root_ptr);
 // printf("\n");
  bst_node_t *del_node = search(*root_ptr, value);
  if (del_node == NULL) return;
  if (del_node->left == NULL && del_node->right == NULL) {
    bst_node_t *parent = del_node->parent;
    if (parent == NULL) {
      *root_ptr = NULL;
     // display_tree(*root_ptr);
     // printf("\n");
      return;
    }
    if (parent->right == del_node) parent->right = NULL;
    else parent->left = NULL;
    free(del_node);
    //display_tree(*root_ptr);
   // printf("\n");
    return;
  }
  if (del_node->left == NULL || del_node->right == NULL) {
    bst_node_t *parent = del_node->parent;
    bst_node_t *successor = (del_node->right == NULL) ? del_node->left : del_node->right;
    if (parent == NULL) {
      successor->parent = NULL;
      *root_ptr = successor;
      free(del_node);
      //display_tree(*root_ptr);
      //printf("\n");
      return;
    }
    successor->parent = parent;
    if (parent->right == del_node) parent->right = successor;
    else parent->left = successor;
    free(del_node);
    //display_tree(*root_ptr);
   // printf("\n");
    return;
  }
  bst_node_t *successor = getSuccessor(del_node->right);
  bst_node_t *parent = del_node->parent;
  if (successor == del_node->right) {
    successor->parent = parent;
    if (parent != NULL) {
      if (parent->right == del_node) parent->right = successor;
      else parent->left = successor;
    } else {
      *root_ptr = successor;
    }
    del_node->left->parent = successor;
    successor->left = del_node->left;
    free(del_node);
    //display_tree(*root_ptr);
    //printf("\n");
    return;
  } else {
    successor->parent->left = successor->right;
    if (successor->right != NULL) successor->right->parent = successor->parent;
    del_node->right->parent = successor;
    successor->right = del_node->right;
    del_node->left->parent = successor;
    successor->left = del_node->left;
    successor->parent = parent;
    if (parent != NULL) {
      if (parent->right == del_node) parent->right = successor;
      else parent->left = successor;
    } else {
      *root_ptr = successor;
    }
    free(del_node);
  }
 // display_tree(*root_ptr);
  //printf("\n");
}

