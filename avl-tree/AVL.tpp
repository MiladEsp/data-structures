#include "AVL.h"

/*************** AVL class: public functions ***************/

template <typename K, typename D>
AVL<K, D>::AVL() : root(nullptr) {}

template <typename K, typename D>
AVL<K, D>::~AVL() { clearTree(); }

template <typename K, typename D>
const D &AVL<K, D>::find(const K &key)
{
    TreeNode *&node = find(key, root);

    if (!node) { throw std::runtime_error("Key not found!"); }

    return node->data;
}

template <typename K, typename D>
void AVL<K, D>::insert(const K &key, const D &data)
{
    findAndInsert(const K &key, const D &data);
}

template <typename K, typename D>
const D &AVL<K, D>::remove(const K &key)
{
    const D &d = findAndRemove(key, root);
    return d;
}

template <typename K, typename D>
bool AVL<K, D>::empty() const { return !root; }

template <typename K, typename D>
bool AVL<K, D>::contains(const K &key)
{
    TreeNode *&node = find(key, root);
    return node != nullptr;
}

/*************** AVL class: private functions ***************/

template <typename K, typename D>
void AVL<K, D>::clearTree()
{
    while (root) { remove(root->key); }
}

template <typename K, typename D>
int AVL<K, D>::getHeight(TreeNode *&node) const
{
    if (!node)
        return -1;
    else
        return node->height;
}

template <typename K, typename D>
int AVL<K, D>::getBalanceFactor(TreeNode *&node) const
{
    if (!node)
        return 0;
    else
        return getHeight(node->right) - getHeight(node->left);
}

/*************** TreeNode class functions ***************/

template <typename K, typename D>
AVL<K, D>::TreeNode::TreeNode(const K &key, const D &data) : key(key), data(data), left(nullptr), right(nullptr), height(0) {}

template <typename K, typename D>
AVL<K, D>::TreeNode::~TreeNode() {}