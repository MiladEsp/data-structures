#pragma once

template <typename T>
class List
{
public:
    List();
    ~List();

    const T& operator[](unsigned index) const;
    void insertAtFront(const T &data);

private:
    class ListNode
    {
    public:
        T data;
        ListNode *next;
        ListNode(const T &data);
        ~ListNode();
    };

    ListNode *head_;

    ListNode* find(const T &data);
};

#include "List.tpp"