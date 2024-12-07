#include <deepstate/DeepState.hpp>
#include "BinaryTree.h"

using namespace deepstate;

// Single test function to comprehensively test tree operations
TEST(BinaryTree, ComprehensiveTest) {
    // Create an empty binary tree
    Node* tree = NULL;

    // Symbolic inputs for keys and values
    int keys[5];
    int values[5];
    for (int i = 0; i < 5; i++) {
        keys[i] = DeepState_Int();
        values[i] = DeepState_Int();
    }

    // Ensure all keys are distinct
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            ASSUME_NE(keys[i], keys[j]);
        }
    }

    // Insert nodes into the tree and verify using in-order traversal
    for (int i = 0; i < 5; i++) {
        tree = insert(tree, keys[i], values[i]);
        int* result = search(tree, keys[i]);
        ASSERT_NE(result, nullptr);  // Key must exist after insertion
        ASSERT_EQ(*result, values[i]);  // Value must match inserted value
    }

    // Print the tree structure after insertions
    printf("Tree structure after insertions:\n");
    printTree(tree, 0);

    // Perform in-order traversal
    printf("In-order traversal after insertions:\n");
    inOrderTraversal(tree);

    // Perform reverse in-order traversal
    printf("Reverse in-order traversal:\n");
    reverseInOrderTraversal(tree);

    // Validate tree properties
    ASSERT_TRUE(isBalanced(tree));  // Tree must be height-balanced
    ASSERT_EQ(countNodes(tree), 5);  // Node count must equal 5
    printf("Tree height: %d\n", getHeight(tree));

    // Find the minimum and maximum nodes
    Node* minNode = findMin(tree);
    Node* maxNode = findMax(tree);
    ASSERT_NE(minNode, nullptr);
    ASSERT_NE(maxNode, nullptr);

    // Verify the minimum and maximum nodes
    printf("Minimum key: %d, Value: %d\n", minNode->key, minNode->value);
    printf("Maximum key: %d, Value: %d\n", maxNode->key, maxNode->value);

    // Check against the manually calculated min and max
    int expectedMin = keys[0];
    int expectedMax = keys[0];
    for (int i = 1; i < 5; i++) {
        if (keys[i] < expectedMin) expectedMin = keys[i];
        if (keys[i] > expectedMax) expectedMax = keys[i];
    }
    ASSERT_EQ(minNode->key, expectedMin);
    ASSERT_EQ(maxNode->key, expectedMax);

    // Delete keys and validate height decreases
    int prevHeight = getHeight(tree);
    for (int i = 0; i < 5; i++) {
        printf("Deleting key: %d\n", keys[i]);
        tree = deleteNode(tree, keys[i]);
        int* result = search(tree, keys[i]);
        ASSERT_EQ(result, nullptr);  // Deleted key must not exist

        printf("Tree structure after deletion of key %d:\n", keys[i]);
        printTree(tree, 0);

        // Check height decreases or remains the same
        int newHeight = getHeight(tree);
        ASSERT_LE(newHeight, prevHeight);
        prevHeight = newHeight;
    }

    // Verify tree is empty
    ASSERT_EQ(countNodes(tree), 0);  // No nodes should remain
    ASSERT_TRUE(isBalanced(tree));  // An empty tree is balanced

    // Clean up
    destroyTree(tree);
    printf("All operations completed successfully.\n");
}
