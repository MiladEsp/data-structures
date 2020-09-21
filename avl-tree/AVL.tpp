#include "AVL.h"

template <typename K, typename D>
AVL<K, D>::AVL() : root_(nullptr) {}

template <typename K, typename D>
AVL<K, D>::~AVL() { clearTree(); }

template <typename K, typename D>
void AVL<K, D>::clearTree()
{
    while (root_)
    {
        remove(root_->key);
    }
}

template <typename K, typename D>
const D& AVL<K, D>::remove(const K& key)
{
    
}

template <typename K, typename D>
AVL<K, D>::TreeNode::TreeNode(const K &key, const D &data) : key(key), data(data), left(nullptr), right(nullptr), height(0) {}

template <typename K, typename D>
AVL<K, D>::TreeNode::~TreeNode() {}