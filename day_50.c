#include <stdio.h>
#include <stdlib.h>

// Definition of BST node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into BST
struct Node* insert(struct Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }

    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }

    return root;
}

// Search in BST
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// Main function
int main() {
    int n, key, val;
    struct Node* root = NULL;

    // Input number of nodes
    scanf("%d", &n);

    // Input elements and insert into BST
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    // Input key to search
    scanf("%d", &key);

    // Search operation
    struct Node* result = search(root, key);

    // Output result
    if (result != NULL) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    return 0;
}