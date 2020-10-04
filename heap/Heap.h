#pragma once

template <typename T>
class Heap {
public:
    Heap();
    ~Heap();

    void insert(const T key);
    T removeMin();

private:
    size_t size;
    size_t capacity;
    T* item;

    void heapifyUP(size_t index);
    void heapifyDown(size_t index);
    void heapifyDown();
    void growArray();

    int parent(size_t index) const;
    int minChild(size_t index) const;
    bool isRoot(size_t index) const;
    bool isLeaf(size_t index) const;
};

#include "Heap.tpp"