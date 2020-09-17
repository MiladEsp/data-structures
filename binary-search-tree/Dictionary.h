#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>

template <typename K, typename D>
class Dictionary
{
public:
    Dictionary();
    ~Dictionary();

    const D& find(const K &key);
    void insert(const K &key, const D &data);
    const D& remove(const K &key);
    bool empty() const;

private:
    class TreeNode
    {
    public:
        const K &key;
        const D &data;

        TreeNode *left;
        TreeNode *right;

        TreeNode(const K &key, const D &data);
        ~TreeNode();
    };

    TreeNode *root_;

    TreeNode*& find_(const K &key, TreeNode *&current_node) const;
    const D& remove_(TreeNode *&node);

    TreeNode*& iop_of_(TreeNode*& current_node) const;
    TreeNode*& rightmost_of_(TreeNode*& current_node) const;
    TreeNode*& swap_nodes_(TreeNode*& node1, TreeNode*& node2);

    void clear_tree();
};

#include "Dictionary.tpp"