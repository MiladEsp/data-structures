#pragma once
#include <iostream>
#include <vector>
#include <queue>

template <typename T>
class BinaryTree
{
public:
    BinaryTree();
    BinaryTree(const std::vector<T> &contents);
    BinaryTree(const BinaryTree &) = delete; // to avoid shallow copy of the tree
    ~BinaryTree();

    void traverseTree(const std::string &mode);

private:
    class TreeNode
    {
    public:
        T data;
        TreeNode *left;
        TreeNode *right;

        TreeNode();
        TreeNode(const T &data);
        ~TreeNode();
    };

    TreeNode *root_;

    void createCompleteTree(const std::vector<T> &contents);
    void destroySubTree(TreeNode *subtree_root);
    void destroyWholeTree();

    void preOrder(TreeNode *current_node);
    void inOrder(TreeNode *current_node);
    void postOrder(TreeNode *current_node);

    void shout(TreeNode *current_node);
};

#include "BinaryTree.tpp"