#include "BinaryTree.h"

template <typename T>
BinaryTree<T>::BinaryTree()  : root_(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree(const std::vector<T> &contents) : BinaryTree()
{
    createCompleteTree(contents);
}

template <typename T>
BinaryTree<T>::~BinaryTree() { destroyWholeTree(); }

template <typename T>
void BinaryTree<T>::createCompleteTree(const std::vector<T> &contents)
{
    destroyWholeTree();

    if (contents.empty())
        return;

    root_ = new TreeNode(contents[0]);

    std::queue<TreeNode**> child_ptrptr_queue;

    child_ptrptr_queue.push(&(root_->left));
    child_ptrptr_queue.push(&(root_->right));

    for (int i = 1; i < contents.size(); i++)
    {
        TreeNode **child_ptrptr = child_ptrptr_queue.front();
        child_ptrptr_queue.pop();

        TreeNode *&actual_child_ptr = *child_ptrptr;
        actual_child_ptr = new TreeNode(contents[i]);

        child_ptrptr_queue.push(&(actual_child_ptr->left));
        child_ptrptr_queue.push(&(actual_child_ptr->right));
    }
}

template <typename T>
void BinaryTree<T>::destroySubTree(TreeNode *subtree_root)
{
    if (!subtree_root)
    {
        return;
    }

    destroySubTree(subtree_root->left);
    destroySubTree(subtree_root->right);

    subtree_root->left = nullptr;
    subtree_root->right = nullptr;

    delete subtree_root;
}

template <typename T>
void BinaryTree<T>::destroyWholeTree()
{
    destroySubTree(root_);
    root_ = nullptr;
}

template <typename T>
void BinaryTree<T>::traverseTree(const std::string &mode)
{
    if (mode == "preOrder")
    {
        preOrder(root_);
    }
    else if (mode == "inOrder")
    {
        inOrder(root_);
    }
    else if (mode == "postOrder")
    {
        postOrder(root_);
    }
}

template <typename T>
void BinaryTree<T>::preOrder(TreeNode *current_node)
{
    if (current_node)
    {
        shout(current_node);
        preOrder(current_node->left);
        preOrder(current_node->right);
    }
}

template <typename T>
void BinaryTree<T>::inOrder(TreeNode *current_node)
{
    if (current_node)
    {
        inOrder(current_node->left);
        shout(current_node);
        inOrder(current_node->right);
    }
}

template <typename T>
void BinaryTree<T>::postOrder(TreeNode *current_node)
{
    if (current_node)
    {
        postOrder(current_node->left);
        postOrder(current_node->right);
        shout(current_node);
    }
}

template <typename T>
void BinaryTree<T>::shout(TreeNode *current_node)
{
    if (current_node)
    {
        std::cout << current_node->data;
    }
    std::cout << " ";
}

template <typename T>
BinaryTree<T>::TreeNode::TreeNode() : left(nullptr), right(nullptr) {}

template <typename T>
BinaryTree<T>::TreeNode::TreeNode(const T &data) : data(data), left(nullptr), right(nullptr) {}

template <typename T>
BinaryTree<T>::TreeNode::~TreeNode() {}