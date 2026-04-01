#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Create new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Count total nodes
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Check Complete Binary Tree
int isComplete(struct Node* root, int index, int totalNodes) {
    if (root == NULL)
        return 1;

    if (index >= totalNodes)
        return 0;

    return isComplete(root->left, 2 * index + 1, totalNodes) &&
           isComplete(root->right, 2 * index + 2, totalNodes);
}

// Check Heap Property
int isHeap(struct Node* root) {
    // Leaf node
    if (root->left == NULL && root->right == NULL)
        return 1;

    // Only left child
    if (root->right == NULL) {
        return (root->data <= root->left->data) &&
               isHeap(root->left);
    }

    // Both children
    if (root->data <= root->left->data &&
        root->data <= root->right->data) {
        return isHeap(root->left) && isHeap(root->right);
    }

    return 0;
}

// Build tree from level order array
struct Node* buildTree(int arr[], int i, int n) {
    if (i >= n)
        return NULL;

    struct Node* root = newNode(arr[i]);
    root->left = buildTree(arr, 2*i + 1, n);
    root->right = buildTree(arr, 2*i + 2, n);

    return root;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct Node* root = buildTree(arr, 0, n);

    int totalNodes = countNodes(root);

    if (isComplete(root, 0, totalNodes) && isHeap(root))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}