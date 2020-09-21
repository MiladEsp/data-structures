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

    bool empty() const;
    const D& remove(const K& key);

private:
    class TreeNode
    {
        const K &key;
        const D &data;
        TreeNode *left;
        TreeNode *right;
        int height;

        TreeNode(const K &key, const D &data);
        ~TreeNode();
    };

    TreeNode *root_;

    void clearTree();
};

#include "AVL.tpp"
