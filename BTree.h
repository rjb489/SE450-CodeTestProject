#ifndef B_TREE_H
#define B_TREE_H

#include <stdbool.h>

// Define the structure for a binary tree node
typedef struct Node {
    int key;
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// Function prototypes
Node* createNode(int key, int value);
Node* insert(Node* root, int key, int value);
int* search(Node* root, int key);
Node* deleteNode(Node* root, int key);
void destroyTree(Node* root);

Node* findMax(Node* root);
Node* findMin(Node* root);

int getHeight(Node* root);
int countNodes(Node* root);
bool isBalanced(Node* root);

void inOrderTraversal(Node* root);
void reverseInOrderTraversal(Node* root);
void preOrderTraversal(Node* root);
void postOrderTraversal(Node* root);

void printTree(Node* root, int space);

#endif // B_TREE_H
