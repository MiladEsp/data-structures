#include "AVL.h"

/*************** AVL class: public functions ***************/

template <typename K, typename D>
AVL<K, D>::AVL() : root(nullptr) {}

template <typename K, typename D>
AVL<K, D>::~AVL() { clearTree(); }

template <typename K, typename D>
const D& AVL<K, D>::find(const K& key) {
    TreeNode*& node = find(key, root);

    if (!node) {
        throw std::runtime_error("ERROR: Key not found");
    }

    return node->data;
}

template <typename K, typename D>
void AVL<K, D>::insert(const K& key, const D& data) {
    findAndInsert(key, data);
}

template <typename K, typename D>
const D& AVL<K, D>::remove(const K& key) {
    const D& d = findAndRemove(key, root);
    return d;
}

template <typename K, typename D>
bool AVL<K, D>::empty() const { return !root; }

template <typename K, typename D>
bool AVL<K, D>::contains(const K& key) {
    TreeNode*& node = find(key, root);
    return node != nullptr;
}

/*************** AVL class: private functions ***************/
template <typename K, typename D>
typename AVL<K, D>::TreeNode*& AVL<K, D>::find(const K& key, TreeNode*& current_node) const {
    if (!current_node)
        return current_node;
    else if (key == current_node->key)
        return current_node;
    else if (key < current_node->key)
        return find(key, current_node->left);
    else
        return find(key, current_node->right);
}

template <typename K, typename D>
const D& AVL<K, D>::remove(TreeNode*& node) {
    if (!node)
        throw std::runtime_error("ERROR: remove_ used on non-existent key");

    // Zero child remove
    if (node->left == nullptr && node->right == nullptr) {
        const D& data = node->data;

        delete node;
        node = nullptr;

        return data;
    }
    // One child (left) remove
    else if (node->left != nullptr && node->right == nullptr) {
        const D& data = node->data;
        TreeNode*& temp = node;
        node = node->left;
        delete temp;
        temp = nullptr;
        return data;
    }
    // One child (right) remove
    else if (node->right != nullptr && node->left == nullptr) {
        const D& data = node->data;
        TreeNode*& temp = node;
        node = node->right;
        delete temp;
        temp = nullptr;
        return data;
    }
    // Two child remove
    else {
        return iopRemove(node);
    }
}

template <typename K, typename D>
void AVL<K, D>::findAndInsert(const K& key, const D& data, TreeNode*& current_node) {
}

template <typename K, typename D>
const D& AVL<K, D>::findAndRemove(const K& key, TreeNode*& current_node) {
}

template <typename K, typename D>
typename AVL<K, D>::TreeNode*& AVL<K, D>::swapNodes(TreeNode*& node1, TreeNode*& node2) {
    TreeNode* orig_node1 = node1;
    TreeNode* orig_node2 = node2;

    if (node1->left == node2) {
        std::swap(node1->right, node2->right);

        node1->left = orig_node2->left;
        orig_node2->left = node1;
        node1 = orig_node2;

        return node1->left;
    } else if (node1->right == node2) {
        std::swap(node1->left, node2->left);

        node1->right = orig_node2->right;
        orig_node2->right = node1;
        node1 = orig_node2;

        return node1->right;
    } else if (node2->left == node1) {
        std::swap(node2->right, node1->right);

        node2->left = orig_node1->left;
        orig_node1->left = node2;
        node2 = orig_node1;

        return node2->left;
    } else if (node2->right == node1) {
        std::swap(node2->left, node1->left);

        node2->right = orig_node1->right;
        orig_node1->right = node2;
        node2 = orig_node1;

        return node2->right;
    } else {
        std::swap(node1->left, node2->left);
        std::swap(node1->right, node2->right);
        std::swap(node1, node2);

        return node2;
    }
}

template <typename K, typename D>
const D& AVL<K, D>::iopRemove(TreeNode*& target_node) {
}

template <typename K, typename D>
const D& AVL<K, D>::iopRemove(TreeNode*& target_node, TreeNode*& iop_ancestor, bool is_initial_call) {
}

template <typename K, typename D>
void AVL<K, D>::clearTree() {
    while (root) {
        remove(root->key);
    }
}

template <typename K, typename D>
int AVL<K, D>::getHeight(TreeNode*& node) const {
    if (!node)
        return -1;
    else
        return node->height;
}

template <typename K, typename D>
int AVL<K, D>::getBalanceFactor(TreeNode*& node) const {
    if (!node)
        return 0;
    else
        return getHeight(node->right) - getHeight(node->left);
}

template <typename K, typename D>
void AVL<K, D>::updateHeight(TreeNode*& current_node) {
    if (!current_node)
        return;

    current_node->height += std::max(getHeight(current_node->left), getHeight(current_node->right));
}

template <typename K, typename D>
void AVL<K, D>::ensureBalance(TreeNode*& current_node) {
}

template <typename K, typename D>
void AVL<K, D>::rotateLeft(TreeNode*& current_node) {
    if (!current_node)
        throw std::runtime_error("ERROR: rotateLeft called on nullptr");
    if (!current_node->right)
        throw std::runtime_error("ERROR: rotateLeft: right child is nullptr");

    TreeNode* x = current_node;
    TreeNode* y = current_node->right;
    TreeNode* z = current_node->right->left;

    x->right = z;
    y->left = x;
    current_node = y;

    updateHeight(x);
    updateHeight(y);
}

template <typename K, typename D>
void AVL<K, D>::rotateRight(TreeNode*& current_node) {
    if (!current_node)
        throw std::runtime_error("ERROR: rotateRight called on nullptr");
    if (!current_node->left)
        throw std::runtime_error("ERROR: rotateRight: left child is nullptr");

    TreeNode* x = current_node;
    TreeNode* y = current_node->left;
    TreeNode* z = current_node->left->right;

    x->left = z;
    y->right = x;
    current_node = y;

    updateHeight(x);
    updateHeight(y);
}

template <typename K, typename D>
void AVL<K, D>::rotateLeftRight(TreeNode*& current_node) {
    if (!current_node)
        throw std::runtime_error("ERROR: rotateLeftRight called on nullptr");

    rotateRight(current_node->left);
    rotateLeft(current_node);
}

template <typename K, typename D>
void AVL<K, D>::rotateRightLeft(TreeNode*& current_node) {
    if (!current_node)
        throw std::runtime_error("ERROR: rotateRightLeft called on nullptr");

    rotateRight(current_node->right);
    rotateLeft(current_node);
}

/*************** TreeNode class functions ***************/

template <typename K, typename D>
AVL<K, D>::TreeNode::TreeNode(const K& key, const D& data) : key(key), data(data), left(nullptr), right(nullptr), height(0) {}

template <typename K, typename D>
AVL<K, D>::TreeNode::~TreeNode() {}