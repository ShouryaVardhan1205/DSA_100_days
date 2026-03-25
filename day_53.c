#include <stdio.h>
#include <stdlib.h>

// Tree Node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Queue Node (for BFS with HD)
struct QNode {
    struct TreeNode* node;
    int hd;
};

// Create new tree node
struct TreeNode* newNode(int val) {
    struct TreeNode* temp = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    temp->val = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Build tree from level order
struct TreeNode* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    struct TreeNode* root = newNode(arr[0]);

    struct TreeNode* queue[2000];
    int front = 0, rear = 0;

    queue[rear++] = root;
    int i = 1;

    while (i < n) {
        struct TreeNode* curr = queue[front++];

        // Left child
        if (i < n && arr[i] != -1) {
            curr->left = newNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;

        // Right child
        if (i < n && arr[i] != -1) {
            curr->right = newNode(arr[i]);
            queue[rear++] = curr->right;
        }
        i++;
    }

    return root;
}

// Vertical Order Traversal
void verticalOrder(struct TreeNode* root) {
    if (!root) return;

    struct QNode queue[2000];
    int front = 0, rear = 0;

    // Store values by HD (shifted index)
    int table[4000][100];  // HD range + nodes per column
    int count[4000] = {0};

    int offset = 2000; // to handle negative HD

    // Start BFS
    queue[rear++] = (struct QNode){root, 0};

    int minHD = 0, maxHD = 0;

    while (front < rear) {
        struct QNode temp = queue[front++];
        struct TreeNode* node = temp.node;
        int hd = temp.hd;

        int index = hd + offset;

        table[index][count[index]++] = node->val;

        if (hd < minHD) minHD = hd;
        if (hd > maxHD) maxHD = hd;

        if (node->left)
            queue[rear++] = (struct QNode){node->left, hd - 1};
        if (node->right)
            queue[rear++] = (struct QNode){node->right, hd + 1};
    }

    // Print result
    for (int i = minHD; i <= maxHD; i++) {
        int index = i + offset;
        for (int j = 0; j < count[index]; j++) {
            printf("%d ", table[index][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct TreeNode* root = buildTree(arr, n);

    verticalOrder(root);

    return 0;
}