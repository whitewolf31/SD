#include <stdlib.h>
#include <numeric>
#include <math.h>

#include "bst_node.h"
#include "helpers.h"



static float test_serialize() {
    std::vector<double> expected(3, 2.0 / 3.0);
    std::vector<double> results(expected.size(), 0.0);

    bst_node_t *root = NULL;
    insert(root, 2.3);
    insert(root, 15.0);
    insert(root, 7.0);
    insert(root, 23.0);
    insert(root, 13.0);
    insert(root, 20.0);
    insert(root, 1.0);
    insert(root, 27.0);
    const char *serialization1 = "(( 1.00 ) 2.30 (( 7.00 ( 13.00 )) 15.00 "
        "(( 20.00 ) 23.00 ( 27.00 ))))";
    results[0] = strcmp(serialize(root), serialization1) == 0;

    root = NULL;
    insert(root, 15.0);
    insert(root, 23.0);
    insert(root, 2.3);
    insert(root, 1.0);
    insert(root, 13.0);
    insert(root, 27.0);
    insert(root, 1920.20);
    insert(root, 7.0);
    insert(root, 20.0);
    const char *serialization2 = "((( 1.00 ) 2.30 (( 7.00 ) 13.00 )) 15.00 "
        "(( 20.00 ) 23.00 ( 27.00 ( 1920.20 ))))";
    results[1] = strcmp(serialize(root), serialization2) == 0;

    root = NULL;
    insert(root, 15.0);
    insert(root, 23.0);
    insert(root, 7.0 );
    insert(root, 13.0);
    insert(root, 1.0 );
    insert(root, 20.0);
    insert(root, 27.0);
    insert(root, 21.0);
    insert(root, 24.0);
    const char *serialization3 = "((( 1.00 ) 7.00 ( 13.00 )) 15.00 "
        "(( 20.00 ( 21.00 )) 23.00 (( 24.00 ) 27.00 )))";
    results[2] = strcmp(serialization3, serialize(root)) == 0;

    show_results(1.1, "serialize", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}

static bool bst_node_equals(const bst_node_t *t1, const bst_node_t *t2) {
    if ((t1 && !t2) || (!t1 && t2)) {
        return false;
    } else if (!t1 && !t2) {
        return true;
    } else {
        return fabs(t1->value - t2->value) < 0.001;
    }
}

static bool bst_equals(const bst_node_t *t1, const bst_node_t *t2) {
    if ((t1 && !t2) || (!t1 && t2)) {
        return false;
    } else if (!t1 && !t2) {
        return true;
    } else {
        bool value_equals = bst_node_equals(t1, t2);
        bool parent_value_equals = bst_node_equals(t1->parent, t2->parent);
        bool left_children_equals = bst_equals(t1->left, t2->left);
        bool right_children_equals = bst_equals(t1->right, t2->right);
        bool equals = value_equals
            && parent_value_equals
            && left_children_equals
            && right_children_equals;
        return equals;
    }
}

static float test_deserialize() {
    std::vector<double> expected(3, 4.0 / 3.0);
    std::vector<double> results(expected.size(), 0.0);
    bst_node_t *root = NULL;
    bst_node_t *reconsructed_root = NULL;

    root = NULL;
    insert(root, 2.3);
    insert(root, 15.0);
    insert(root, 7.0);
    insert(root, 23.0);
    insert(root, 13.0);
    insert(root, 20.0);
    insert(root, 1.0);
    insert(root, 27.0);
    const char *serialization1 = "(( 1.00 ) 2.30 (( 7.00 ( 13.00 )) 15.00 "
        "(( 20.00 ) 23.00 ( 27.00 ))))";
    reconsructed_root = deserialize(serialization1);
    results[0] = bst_equals(root, reconsructed_root);

    root = NULL;
    insert(root, 15.0);
    insert(root, 23.0);
    insert(root, 2.3);
    insert(root, 1.0);
    insert(root, 13.0);
    insert(root, 27.0);
    insert(root, 1920.20);
    insert(root, 7.0);
    insert(root, 20.0);
    const char *serialization2 = "((( 1.00 ) 2.30 (( 7.00 ) 13.00 )) 15.00 "
            "(( 20.00 ) 23.00 ( 27.00 ( 1920.20 ))))";
    reconsructed_root = deserialize(serialization2);
    results[1] = bst_equals(root, reconsructed_root);

    root = NULL;
    insert(root, 15.0);
    insert(root, 23.0);
    insert(root, 7.0 );
    insert(root, 13.0);
    insert(root, 1.0 );
    insert(root, 20.0);
    insert(root, 27.0);
    insert(root, 21.0);
    insert(root, 24.0);
    const char *serialization3 = "((( 1.00 ) 7.00 ( 13.00 )) 15.00 "
        "(( 20.00 ( 21.00 )) 23.00 (( 24.00 ) 27.00 )))";
    reconsructed_root = deserialize(serialization3);
    results[2] = bst_equals(root, reconsructed_root);


    show_results(1.2, "deserialize", expected, results);
    return std::accumulate(results.begin(), results.end(), 0.0) / results.size();
}


float test_exercise1() {
    std::vector<double> expected = {2.0, 4.0};
    std::vector<double> results(expected.size(), 0);

    results[0] = test_serialize();
    results[1] = test_deserialize();

    show_results(1.0, "serialize & deserialize", expected, results);
    double total = 0;
    for (size_t idx = 0; idx < results.size(); idx ++) {
        total += results[idx] * expected[idx];
    }
    return total;
}
