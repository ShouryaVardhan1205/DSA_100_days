#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

// Build tree from level-order input
struct TreeNode* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    
    struct TreeNode** queue = (struct TreeNode**)malloc(n * sizeof(struct TreeNode*));
    int front = 0, rear = 0;
    
    struct TreeNode* root = newNode(arr[0]);
    queue[rear++] = root;
    int i = 1;
    
    while (front < rear && i < n) {
        struct TreeNode* curr = queue[front++];
        
        if (i < n && arr[i] != -1) {
            curr->left = newNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;
        
        if (i < n && arr[i] != -1) {
            curr->right = newNode(arr[i]);
            queue[rear++] = curr->right;
        }
        i++;
    }
    
    free(queue);
    return root;
}

// Mirror the tree
void mirror(struct TreeNode* root) {
    if (root == NULL) return;
    
    // Swap left and right
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    mirror(root->left);
    mirror(root->right);
}

// Inorder traversal
void inorder(struct TreeNode* root, int* first) {
    if (root == NULL) return;
    inorder(root->left, first);
    if (*first) *first = 0;
    else printf(" ");
    printf("%d", root->val);
    inorder(root->right, first);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    
    struct TreeNode* root = buildTree(arr, n);
    mirror(root);
    
    int first = 1;
    inorder(root, &first);
    printf("\n");
    
    free(arr);
    return 0;
}
```

**How it works:**
```
Original:          Mirrored:
    1                  1
   / \                / \
  2   3      →       3   2
 / \ / \            / \ / \
4  5 6  7          7  6 5  4

Inorder of mirrored: 7 3 6 1 5 2 4 ✓