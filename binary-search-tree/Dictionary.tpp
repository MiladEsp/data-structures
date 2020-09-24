#include "Dictionary.h"

template <typename K, typename D>
Dictionary<K, D>::Dictionary() : root_(nullptr) {}

template <typename K, typename D>
Dictionary<K, D>::~Dictionary() { clearTree(); }

template <typename K, typename D>
void Dictionary<K, D>::clearTree() {
    while (root_) {
        remove(root_->key);
    }
}

template <typename K, typename D>
bool Dictionary<K, D>::empty() const { return !root_; }

template <typename K, typename D>
const D& Dictionary<K, D>::find(const K& key) {
    TreeNode*& node = find_(key, root_);
    if (!node)
        throw std::runtime_error("Key not found!");
    return node->data;
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::find_(const K& key, TreeNode*& current_node) const {
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
void Dictionary<K, D>::insert(const K& key, const D& data) {
    TreeNode*& node = find_(key, root_);
    if (node)
        throw std::runtime_error("Key already exists!");
    node = new TreeNode(key, data);
}

template <typename K, typename D>
const D& Dictionary<K, D>::remove(const K& key) {
    TreeNode*& node = find_(key, root_);
    if (!node)
        throw std::runtime_error("Key not found!");
    return remove_(node);
}

template <typename K, typename D>
const D& Dictionary<K, D>::remove_(TreeNode*& node) {
    if (!node)
        throw std::runtime_error("remove_ used on non-existent key!");

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
        TreeNode*& iop = iopOf_(node);

        if (!iop)
            throw std::runtime_error("IOP not found!");

        TreeNode*& moved_node = swapNodes_(node, iop);

        return remove_(moved_node);
    }
}

// finds the in-order predecessor of the current ndoe
template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::iopOf_(TreeNode*& current_node) const {
    if (!current_node)
        return current_node;

    if (!(current_node->left))
        return current_node->left;

    return rightmostOf_(current_node->left);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::rightmostOf_(TreeNode*& current_node) const {
    if (!current_node)
        return current_node;

    if (!(current_node->right))
        return current_node;

    return rightmostOf_(current_node->right);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::swapNodes_(TreeNode*& node1, TreeNode*& node2) {
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
void Dictionary<K, D>::printInOrder() { printInOrder_(root_); }

template <typename K, typename D>
void Dictionary<K, D>::printInOrder_(TreeNode* node) {
    if (!node) {
        std::cout << " ";
        return;
    } else {
        printInOrder_(node->left);
        std::cout << "[" << node->key << " : " << node->data << "]";
        printInOrder_(node->right);
    }
}

template <typename K, typename D>
Dictionary<K, D>::TreeNode::TreeNode(const K& key, const D& data) : key(key), data(data), left(nullptr), right(nullptr) {}

template <typename K, typename D>
Dictionary<K, D>::TreeNode::~TreeNode() {}