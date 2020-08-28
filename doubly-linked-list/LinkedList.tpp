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
    ListNode *new_node = new ListNode(new_data);

    if (!head_)
    {
        head_ = new_node;
        tail_ = new_node;
    }
    else
    {
        ListNode *old_head = head_;
        old_head->next = new_node;
        old_head->prev = new_node;
        new_node->next = old_head;
        head_ = new_node;
    }

    size_++;
    
}

template <typename T>
void LinkedList<T>::pushBack(const T &new_data)
{
    ListNode *new_node = new ListNode(new_data);

    if (!head_)
    {
        head_ = new_node;
        tail_ = new_node;
    }
    else
    {
        ListNode *old_tail = tail_;
        old_tail->next = new_node;
        new_node->prev = old_tail;
        tail_ = new_node;
    }

    size_++;
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
void LinkedList<T>::popFront()
{
    if (!head_) return;

    if (!head_->next)
    {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;

        size_--;

        if (0 != size_) throw std::runtime_error("Error in popFront");

        return;
    }

    ListNode *old_head = head_;
    head_ = head_->next;
    head_->prev = nullptr;
    
    delete old_head;
    old_head = nullptr;

    size_--;
}

template <typename T>
void LinkedList<T>::popBack()
{
    if (!head_) return;

    if (!tail_->prev)
    {
        delete tail_;
        head_ = nullptr;
        tail_ = nullptr;

        size_--;

        if (0 != size_) throw std::runtime_error("Error in popBack");
    }

    ListNode *old_tail = tail_;
    tail_ = tail_->prev;
    tail_->next = nullptr;

    delete old_tail;
    old_tail = nullptr;

    size_--;
}

template <typename T>
LinkedList<T>::ListNode::ListNode() : next(nullptr), prev(nullptr) {}

template <typename T>
LinkedList<T>::ListNode::ListNode(const T &data) : next(nullptr), prev(nullptr), data(data) {}

template <typename T>
LinkedList<T>::ListNode::~ListNode() {}