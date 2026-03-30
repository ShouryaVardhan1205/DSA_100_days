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

// Find index of value in inorder array
int findIndex(int* inorder, int start, int end, int val) {
    for (int i = start; i <= end; i++)
        if (inorder[i] == val) return i;
    return -1;
}

// Build tree from preorder and inorder
struct TreeNode* buildTree(int* preorder, int* inorder, int inStart, int inEnd, int* preIndex) {
    if (inStart > inEnd) return NULL;

    // Current root is next element in preorder
    struct TreeNode* root = newNode(preorder[(*preIndex)++]);

    // Find root in inorder to split left and right
    int mid = findIndex(inorder, inStart, inEnd, root->val);

    // Left subtree comes before right in preorder
    root->left  = buildTree(preorder, inorder, inStart, mid - 1, preIndex);
    root->right = buildTree(preorder, inorder, mid + 1, inEnd,   preIndex);

    return root;
}

// Postorder: Left -> Right -> Root
void postorder(struct TreeNode* root, int* first) {
    if (root == NULL) return;
    postorder(root->left,  first);
    postorder(root->right, first);
    if (*first) *first = 0;
    else printf(" ");
    printf("%d", root->val);
}

int main() {
    int n;
    scanf("%d", &n);

    int* preorder = (int*)malloc(n * sizeof(int));
    int* inorder  = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) scanf("%d", &preorder[i]);
    for (int i = 0; i < n; i++) scanf("%d", &inorder[i]);

    int preIndex = 0;
    struct TreeNode* root = buildTree(preorder, inorder, 0, n - 1, &preIndex);

    int first = 1;
    postorder(root, &first);
    printf("\n");

    free(preorder);
    free(inorder);
    return 0;
}