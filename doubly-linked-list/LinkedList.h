#pragma once

#include <stdexcept>

template <typename T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    size_t size() const;
    bool empty() const;
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    void pushFront(const T& new_data);
    void pushBack(const T& new_data);
    void clear();
    void popBack();
    void popFront();

public:
    class ListNode {
    public:
        T data;
        ListNode* next;
        ListNode* prev;

        ListNode();
        ListNode(const T& data);
        ~ListNode();
    };

    ListNode* head_;
    ListNode* tail_;

    size_t size_;
};

#include "LinkedList.tpp"