#include <stdio.h>
#include <stdlib.h>

// Tree node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Queue for level order construction
struct Node* queue[1000];
int front = 0, rear = 0;

void enqueue(struct Node* node) {
    queue[rear++] = node;
}

struct Node* dequeue() {
    return queue[front++];
}

// Build tree from level order input
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1)
        return NULL;

    struct Node* root = newNode(arr[0]);
    enqueue(root);

    int i = 1;

    while (i < n) {
        struct Node* current = dequeue();

        // Left child
        if (i < n && arr[i] != -1) {
            current->left = newNode(arr[i]);
            enqueue(current->left);
        }
        i++;

        // Right child
        if (i < n && arr[i] != -1) {
            current->right = newNode(arr[i]);
            enqueue(current->right);
        }
        i++;
    }

    return root;
}

// LCA function
struct Node* findLCA(struct Node* root, int n1, int n2) {
    if (root == NULL)
        return NULL;

    if (root->data == n1 || root->data == n2)
        return root;

    struct Node* left = findLCA(root->left, n1, n2);
    struct Node* right = findLCA(root->right, n1, n2);

    if (left && right)
        return root;

    return (left != NULL) ? left : right;
}

// Main function
int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int n1, n2;
    scanf("%d %d", &n1, &n2);

    struct Node* root = buildTree(arr, n);

    struct Node* lca = findLCA(root, n1, n2);

    if (lca != NULL)
        printf("%d\n", lca->data);
    else
        printf("LCA not found\n");

    return 0;
}