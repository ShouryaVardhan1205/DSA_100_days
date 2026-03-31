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

// Build tree from inorder and postorder
struct TreeNode* buildTree(int* inorder, int* postorder, int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) return NULL;

    // Current root is last element in postorder (read right to left)
    struct TreeNode* root = newNode(postorder[(*postIndex)--]);

    // Find root in inorder to split left and right
    int mid = findIndex(inorder, inStart, inEnd, root->val);

    // Right before left (postIndex goes right to left)
    root->right = buildTree(inorder, postorder, mid + 1, inEnd,   postIndex);
    root->left  = buildTree(inorder, postorder, inStart, mid - 1, postIndex);

    return root;
}

// Preorder: Root -> Left -> Right
void preorder(struct TreeNode* root, int* first) {
    if (root == NULL) return;
    if (*first) *first = 0;
    else printf(" ");
    printf("%d", root->val);
    preorder(root->left,  first);
    preorder(root->right, first);
}

int main() {
    int n;
    scanf("%d", &n);

    int* inorder   = (int*)malloc(n * sizeof(int));
    int* postorder = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) scanf("%d", &inorder[i]);
    for (int i = 0; i < n; i++) scanf("%d", &postorder[i]);

    int postIndex = n - 1;
    struct TreeNode* root = buildTree(inorder, postorder, 0, n - 1, &postIndex);

    int first = 1;
    preorder(root, &first);
    printf("\n");

    free(inorder);
    free(postorder);
    return 0;
}
```

**How it works:**
```
Inorder:   4 2 5 1 3
Postorder: 4 5 2 3 1
                   ^
               root = 1

Inorder split at 1:
  Left  inorder: [4 2 5]
  Right inorder: [3]

postIndex moves left → next root = 3
  Right subtree: root=3 → no children

postIndex moves left → next root = 2
  Left subtree: root=2 → Left:[4], Right:[5]

Final Tree:
        1
       / \
      2   3
     / \
    4   5

Preorder: 1 2 4 5 3 ✓