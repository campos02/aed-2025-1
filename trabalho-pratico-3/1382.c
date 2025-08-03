#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int Depth(struct TreeNode *root)
{
    if (root == NULL)
        return 0;

    int left = Depth(root->left);
    int right = Depth(root->right);

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

int BalancingFactor(struct TreeNode *root)
{
    if (root == NULL)
        return 0;

    return Depth(root->left) - Depth(root->right);
}

void Balance(struct TreeNode **root)
{
    if (*root == NULL)
        return;

    int balancingFactor = BalancingFactor(*root);
    if (balancingFactor > 1)
    {
        if (BalancingFactor((*root)->left) == -1)
        {
            struct TreeNode *temp = (*root)->left->right;
            (*root)->left->right = temp->left;

            temp->left = (*root)->left;
            (*root)->left = temp->right;

            temp->right = *root;
            *root = temp;
        }
        else
        {
            struct TreeNode *temp = (*root)->left;
            (*root)->left = temp->right;

            temp->right = *root;
            *root = temp;
        }
    }
    else if (balancingFactor < -1)
    {
        if (BalancingFactor((*root)->right) == 1)
        {
            struct TreeNode *temp = (*root)->right->left;
            (*root)->right->left = temp->right;

            temp->right = (*root)->right;
            (*root)->right = temp->left;

            temp->left = *root;
            *root = temp;
        }
        else
        {
            struct TreeNode *temp = (*root)->right;
            (*root)->right = temp->left;

            temp->left = *root;
            *root = temp;
        }
    }

    Balance(&(*root)->left);
    Balance(&(*root)->right);
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode *balanceBST(struct TreeNode *root)
{
    while (BalancingFactor(root) > 1 || BalancingFactor(root) < -1)
    {
        Balance(&root);
    }

    return root;
}