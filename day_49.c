#include <stdio.h>
#include <stdlib.h>

// Define structure for a node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert into BST
struct Node* insert(struct Node* root, int value) {
    // If tree is empty, create new node
    if (root == NULL) {
        return createNode(value);
    }

    // If value is smaller, go left
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    // If value is greater, go right
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Inorder traversal (Left → Root → Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main function
int main() {
    int n, value;
    struct Node* root = NULL;

    // Input number of nodes
    scanf("%d", &n);

    // Input elements and insert into BST
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    // Output inorder traversal
    printf("Inorder Traversal: ");
    inorder(root);

    return 0;
}