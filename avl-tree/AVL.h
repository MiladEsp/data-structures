#pragma once

#include <stdexcept>
#include <utility>
#include <iostream>
#include <algorithm>

template <typename K, typename D>
class AVL
{
public:
    AVL();
    ~AVL();

    const D &find(const K &key);
    void insert(const K &key, const D &data);
    const D &remove(const K &key);

    bool empty() const;
    bool contains(const K &key);

private:
    class TreeNode
    {
    public:
        const K &key;
        const D &data;
        TreeNode *left;
        TreeNode *right;
        int height;

        TreeNode(const K &key, const D &data);
        ~TreeNode();
    };

    TreeNode *root;

    TreeNode *&find(const K &key, TreeNode *&current_node) const;
    const D &remove(TreeNode *&node);
    void findAndInsert(const K &key, const D &data, TreeNode *&current_node);
    const D &findAndRemove(const K &key, TreeNode *&current_node);
    TreeNode *&swapNodes(TreeNode *&node1, TreeNode *&node2);
    const D &iopRemove(TreeNode *&target_node);
    const D &iopRemove(TreeNode *&target_node, TreeNode *&iop_ancestor, bool is_initial_call);

    void clearTree();
    int getHeight(TreeNode *&node) const;
    int getBalanceFactor(TreeNode *&node) const;
    void updateHeight(TreeNode *&current_node);
    void ensureBalance(TreeNode *&current_node);
    void rotateLeft(TreeNode *&current_node);
    void rotateRight(TreeNode *&current_node);
    void rotateLeftRight(TreeNode *&current_node);
    void rotateRightLeft(TreeNode *&current_node);
};

#include "AVL.tpp"
