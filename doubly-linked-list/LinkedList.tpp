#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
LinkedList<T>::~LinkedList() { clear(); }

template <typename T>
size_t LinkedList<T>::size() const { return size_; }

template <typename T>
bool LinkedList<T>::empty() const { return !head_; }

template <typename T>
T& LinkedList<T>::front()
{
    if (!head_)
    {
        throw std::runtime_error("front() called on empty LinkedList");
    }
    else
    {
        return head_->data;
    }
}

template <typename T>
T& LinkedList<T>::back()
{
    if (!head_)
    {
        throw std::runtime_error("front() called on empty LinkedList");
    }
    else
    {
        return tail_->data;
    }
}

template <typename T>
const T &LinkedList<T>::front() const
{
    if (!head_)
    {
        throw std::runtime_error("front() called on empty LinkedList");
    }
    else
    {
        return head_->data;
    }
}

template <typename T>
const T &LinkedList<T>::back() const
{
    if (!head_)
    {
        throw std::runtime_error("front() called on empty LinkedList");
    }
    else
    {
        return tail_->data;
    }
}

template <typename T>
void LinkedList<T>::pushFront(const T &new_data)
{
}

template <typename T>
void LinkedList<T>::pushBack(const T &new_data)
{
}

template <typename T>
void LinkedList<T>::clear()
{
    while (head_)
    {
        popBack();
    }

    if (0 != size_) throw std::runtime_error("Error in clear: ");
}

template <typename T>
void LinkedList<T>::popBack()
{
}

template <typename T>
void LinkedList<T>::popFront()
{
}

template <typename T>
LinkedList<T>::ListNode::ListNode() : next(nullptr), prev(nullptr) {}

template <typename T>
LinkedList<T>::ListNode::ListNode(const T &data) : next(nullptr), prev(nullptr), data(data) {}

template <typename T>
LinkedList<T>::ListNode::~ListNode() {}