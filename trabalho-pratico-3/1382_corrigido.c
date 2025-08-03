#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int Depth(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    
    int left = Depth(root->left);
    int right = Depth(root->right);

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

int BalancingFactor(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    return Depth(root->left) - Depth(root->right);
}

void Balance(struct TreeNode** root) {
    if (*root == NULL)
        return;

    int balancingFactor = BalancingFactor(*root);
    if (balancingFactor > 1) {
        if (BalancingFactor((*root)->left) < 0) {
            struct TreeNode* temp = (*root)->left->right;
            (*root)->left->right = temp->left;

            temp->left = (*root)->left;
            (*root)->left = temp->right;

            temp->right = *root;
            *root = temp;
        } else {
            struct TreeNode* temp = (*root)->left;
            (*root)->left = temp->right;
            
            temp->right = *root;
            *root = temp;
        }
    } else if (balancingFactor < -1) {
        if (BalancingFactor((*root)->right) > 0) {
            struct TreeNode* temp = (*root)->right->left;
            (*root)->right->left = temp->right;

            temp->right = (*root)->right;
            (*root)->right = temp->left;
            
            temp->left = *root;
            *root = temp;
        } else {
            struct TreeNode* temp = (*root)->right;
            (*root)->right = temp->left;
            
            temp->left = *root;
            *root = temp;
        }
    }

    Balance(&(*root)->left);
    Balance(&(*root)->right);
}

int IsBalanced(struct TreeNode* root) {
    if (root == NULL)
        return 1;

    int rootFactor = BalancingFactor(root);
    if (rootFactor > 1 || rootFactor < -1)
        return 0;
    
    if (!IsBalanced(root->left))
        return 0;

    if (!IsBalanced(root->right))
        return 0;

    return 1;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* balanceBST(struct TreeNode* root) {
    while (!IsBalanced(root)) {
        Balance(&root);
    }

    return root;
}