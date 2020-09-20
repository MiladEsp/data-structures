#include "Dictionary.h"

template <typename K, typename D>
Dictionary<K, D>::Dictionary() : root_(nullptr) {}

template <typename K, typename D>
Dictionary<K, D>::~Dictionary() { clear_tree(); }

template <typename K, typename D>
void Dictionary<K, D>::clearTree()
{
    while (root_)
    {
        remove(root_->key);
    }
}

template <typename K, typename D>
bool Dictionary<K, D>::empty() const { return !root_; }

template <typename K, typename D>
const D &Dictionary<K, D>::find(const K &key)
{
    TreeNode *&node = find_(key, root_);
    if (!node)
        throw std::runtime_error("Key not found!");
    return node->data;
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode *&Dictionary<K, D>::find_(const K &key, TreeNode *&current_node) const
{
    if (!current_node)
        return current_node;
    else if (key == current_node->key)
        return current_node;
    else if (key > current_node->key)
        return find_(key, current_node->right);
    else
        return find_(key, current_node->left);
}

template <typename K, typename D>
void Dictionary<K, D>::insert(const K &key, const D &data)
{
    TreeNode *&node = find_(key, root_);
    if (node)
        throw std::runtime_error("Key already exists!");
    node = new TreeNode(key, data);
}

template <typename K, typename D>
const D &Dictionary<K, D>::remove(const K &key)
{
    TreeNode *&node = find_(key, root_);
    if (!node)
        throw std::runtime_error("Key not found!");
    return remove_(node);
}

template <typename K, typename D>
const D &Dictionary<K, D>::remove_(TreeNode *&node)
{
    if (!node)
        throw std::runtime_error("remove_ used on non-existent key!");

    // Zero child remove
    if (node->left == nullptr && node->right == nullptr)
    {
        const D &data = node->data;

        delete node;
        node = nullptr;

        return data;
    }
    // One child (left) remove
    else if (node->left != nullptr && node->right == nullptr)
    {
        const D &data = node->data;
        TreeNode *&temp = node;
        node = node->left;
        delete temp;
        temp = nullptr;
        return data;
    }
    // One child (right) remove
    else if (node->right != nullptr && node->left == nullptr)
    {
        const D &data = node->data;
        TreeNode *&temp = node;
        node = node->right;
        delete temp;
        temp = nullptr;
        return data;
    }
    // Two child remove
    else
    {
        TreeNode *&iop = iopOf(node);

        if (!iop)
            throw std::runtime_error("IOP not found!");

        TreeNode *&moved_node = swapNodes_(node, iop);

        return remove_(moved_node);
    }
}

// finds the in-order predecessor of the current ndoe
template <typename K, typename D>
typename Dictionary<K, D>::TreeNode *&Dictionary<K, D>::iopOf_(TreeNode *&current_node) const
{
    if (!current_node)
        return current_node;

    if (!current_node->left)
        return current_node->left;

    return rightmostOf_(current_node->left);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode *&Dictionary<K, D>::rightmostOf_(TreeNode *&current_node) const
{
    if (!current_node)
        return current_node;

    if (!current_node->right)
        return current_node->right;

    return rightmostOf_(current_node->right);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode *&Dictionary<K, D>::swapNodes_(TreeNode *&node1, TreeNode *&node2)
{
}

template <typename K, typename D>
Dictionary<K, D>::TreeNode::TreeNode(const K &key, const D &data) : key(key), data(data), left(nullptr), right(nullptr) {}

template <typename K, typename D>
Dictionary<K, D>::TreeNode::~TreeNode() {}