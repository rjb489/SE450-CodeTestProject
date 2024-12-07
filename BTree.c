#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for a binary tree node
typedef struct Node {
    int key;
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert a key-value pair into the binary tree
Node* insert(Node* root, int key, int value) {
    if (!root) {
        return createNode(key, value);
    }
    if (key < root->key) {
        root->left = insert(root->left, key, value);
    } else if (key > root->key) {
        root->right = insert(root->right, key, value);
    } else {
        root->value = value; // Update value if the key already exists
    }
    return root;
}

// Search for a key in the binary tree
int* search(Node* root, int key) {
    if (!root) return NULL;
    if (key == root->key) return &(root->value);
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

// Find the minimum value node in a subtree
Node* findMin(Node* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

// Delete a node by key
Node* deleteNode(Node* root, int key) {
    if (!root) return NULL;
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Destroy the binary tree
void destroyTree(Node* root) {
    if (!root) return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

// Print the tree (in-order traversal)
void printTree(Node* root) {
    if (!root) return;
    printTree(root->left);
    printf("Key: %d, Value: %d\n", root->key, root->value);
    printTree(root->right);
}
