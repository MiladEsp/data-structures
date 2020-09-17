#include "Dictionary.h"

template <typename K, typename D>
Dictionary<K, D>::Dictionary() : root_(nullptr) {}

template <typename K, typename D>
Dictionary<K, D>::~Dictionary() { clear_tree(); }

template <typename K, typename D>
void Dictionary<K, D>::clear_tree()
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
    
}

template <typename K, typename D>
Dictionary<K, D>::TreeNode::TreeNode(const K &key, const D &data) : key(key), data(data), left(nullptr), right(nullptr) {}

template <typename K, typename D>
Dictionary<K, D>::TreeNode::~TreeNode() {}