#pragma once

template <typename T>
class List
{
public:
    List();
    ~List();

    const T &operator[](unsigned index) const;
    void insertAtFront(T &data);

private:
    class ListNode
    {
    public:
        T &data;
        ListNode *next;
        ListNode(T &data);
        ~ListNode();
    };

    ListNode *head;

    ListNode *find(T &data);
};

#include "List.tpp"