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
    if (current_node == nullptr) {
        current_node = new TreeNode(key, data);
        return;
    } else if (key == current_node->key) {
        throw std::runtime_error("ERROR: Key already exists.");
    } else if (key < current_node->key) {
        findAndInsert(key, data, current_node->left);
        ensureBalance(current_node);
        return;
    } else {
        findAndInsert(key, data, current_node->right);
        ensureBalance(current_node);
        return;
    }
}

template <typename K, typename D>
const D& AVL<K, D>::findAndRemove(const K& key, TreeNode*& current_node) {
    if (current_node == nullptr) {
        throw std::runtime_error("Error: Key not found to remove.");
    } else if (key == current_node->key) {
        return remove(current_node);
    } else if (key < current_node->key) {
        const D& d = findAndRemove(key, current_node->left);
        ensureBalance(current_node);
        return d;
    } else {
        const D& d = findAndRemove(key, current_node->right);
        ensureBalance(current_node);
        return d;
    }
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
    if (!target_node)
        throw std::runtime_error("ERROR: iopRemove called on nullptr.");

    const D& d = iopRemove(target_node, target_node->left, true);

    if (target_node->left)
        ensureBalance(target_node->left);
    ensureBalance(target_node);

    return d;
}

template <typename K, typename D>
const D& AVL<K, D>::iopRemove(TreeNode*& target_node, TreeNode*& iop_ancestor, bool is_initial_call) {
    if (!target_node) {
        throw std::runtime_error("ERROR: _iopRemove: targetNode is null");
    }

    if (!iop_ancestor) {
        throw std::runtime_error("ERROR: _iopRemove: iopAncestor is null");
    }

    if (iop_ancestor->right != nullptr) {
        const D& d = iopRemove(target_node, iop_ancestor->right, false);

        if (!is_initial_call) {
            if (iop_ancestor)
                ensureBalance(iop_ancestor);
        }
    } else {
        TreeNode*& moved_target = swapNodes(target_node, iop_ancestor);
        const D& d = remove(moved_target);
        return d;
    }
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
    if (!current_node)
        return;

    const int initial_balance = getBalanceFactor(current_node);

    if (initial_balance < -2 || initial_balance > 2) {
        std::string msg("ERROR: invalid initial balance factor: ");
        msg += std::to_string(initial_balance);
        msg += " ; This should never happen.";
        std::cerr << "current node key: " << current_node->key << " current node data: " << current_node->data << std::endl;
        std::cerr << "left node key: " << current_node->left->key << " right node key: " << current_node->right->key << std::endl;
        std::cerr << "left node height: " << getHeight(current_node->left) << " right node height: " << getHeight(current_node->right) << std::endl;
        throw std::runtime_error(msg);
    }

    if (initial_balance == -2) {
        const int l_balance = getBalanceFactor(current_node->left);
        if (l_balance == -1 || l_balance == 0) {
            rotateRight(current_node);
        } else if (l_balance == 1) {
            rotateLeftRight(current_node);
        } else {
            std::string msg("ERROR: l_balance has unexpected value: ");
            msg += std::to_string(l_balance);
            msg += " ; This should never happen here.";
            throw std::runtime_error(msg);
        }
    } else if (initial_balance == 2) {
        const int r_balance = getBalanceFactor(current_node->right);
        if (r_balance == 1 || r_balance == 0) {
            rotateLeft(current_node);
        } else if (r_balance == -1) {
            rotateRightLeft(current_node);
        } else {
            std::string msg("ERROR: r_balance has unexpected value: ");
            msg += std::to_string(r_balance);
            msg += " ; This should never happen here.";
            throw std::runtime_error(msg);
        }
    }

    updateHeight(current_node);

    const int final_balance = getBalanceFactor(current_node);
    if (final_balance < -1 || final_balance > 1) {
        std::string msg("ERROR: Invalid balance factor after ensureBalance: ");
        msg += std::to_string(final_balance);
        msg += " ; Something went wrong.";
        throw std::runtime_error(msg);
    }
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