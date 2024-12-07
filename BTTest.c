#include <deepstate/DeepState.hpp>
#include "BinaryTree.h"

using namespace deepstate;

TEST(BinaryTree, ComprehensiveTest) {
    // Create an empty binary tree
    Node* tree = NULL;

    // Symbolic inputs for keys and values
    int keys[4];
    int values[4];
    for (int i = 0; i < 4; i++) {
        keys[i] = DeepState_Int();
        values[i] = DeepState_Int();
    }

    // Ensure all keys are distinct
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            ASSUME_NE(keys[i], keys[j]);
        }
    }

    // Insert nodes into the tree and verify using in-order traversal
    for (int i = 0; i < 4; i++) {
        tree = insert(tree, keys[i], values[i]);
        int* result = search(tree, keys[i]);
        ASSERT_NE(result, nullptr);  // Key must exist after insertion
        ASSERT_EQ(*result, values[i]);  // Value must match inserted value
    }

    // Print the tree structure after insertions
    printf("Tree structure after insertions:\n");
    printTree(tree, 0);

    // Perform reverse in-order traversal
    printf("Reverse in-order traversal after insertions:\n");
    reverseInOrderTraversal(tree);

    // Validate tree properties
    ASSERT_TRUE(isBalanced(tree));  // Tree must be height-balanced
    ASSERT_EQ(countNodes(tree), 4);  // Node count must equal 4
    printf("Tree height: %d\n", getHeight(tree));

    // Test edge cases: Inserting and searching extreme values
    tree = insert(tree, INT_MIN, 42);
    tree = insert(tree, INT_MAX, 84);
    ASSERT_EQ(*search(tree, INT_MIN), 42);  // Verify INT_MIN insertion
    ASSERT_EQ(*search(tree, INT_MAX), 84);  // Verify INT_MAX insertion

    // Perform in-order traversal and print results
    printf("In-order traversal after extreme value insertions:\n");
    inOrderTraversal(tree);

    // Delete keys and validate height decreases
    int prevHeight = getHeight(tree);
    for (int i = 0; i < 4; i++) {
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

    // Delete extreme values
    tree = deleteNode(tree, INT_MIN);
    tree = deleteNode(tree, INT_MAX);
    ASSERT_EQ(search(tree, INT_MIN), nullptr);
    ASSERT_EQ(search(tree, INT_MAX), nullptr);

    // Validate tree is empty
    ASSERT_EQ(countNodes(tree), 0);  // No nodes should remain
    ASSERT_TRUE(isBalanced(tree));  // An empty tree is balanced

    // Test deleting from an empty tree
    printf("Deleting from an empty tree:\n");
    tree = deleteNode(tree, 12345);  // Should handle gracefully

    // Clean up
    destroyTree(tree);
    printf("All operations completed successfully.\n");
}
