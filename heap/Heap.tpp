#include "Heap.h"

/*************** Heap class: public functions ***************/

template <typename T>
Heap<T>::Heap() {
    size = 0;
    capacity = 2;
    item = new T[capacity + 1];
}

template <typename T>
Heap<T>::~Heap() {
    delete[] item;
    std::cout << std::endl
              << "\nDestroyed the heap." << std::endl;
}

template <typename T>
void Heap<T>::insert(const T key) {
    if (size == capacity)
        growArray();

    size++;
    item[size] = key;

    heapifyUP(size);

    std::cout << "After Heap<T>::insert(key = " << key << "): ";
    for (size_t i = 1; i <= size; i++) {
        std::cout << item[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
T Heap<T>::removeMin() {
    T min_value = item[1];

    std::swap(item[1], item[size--]);

    heapifyDown();

    return min_value;
}

/*************** Heap class: private functions ***************/

template <typename T>
void Heap<T>::heapifyUP(size_t index) {
    if (!isRoot(index)) {
        if (item[index] < item[parent(index)]) {
            std::swap(item[index], item[parent(index)]);
            heapifyUP(parent(index));
        }
    }
}

template <typename T>
void Heap<T>::heapifyDown() {
    heapifyDown(1);
}

template <typename T>
void Heap<T>::heapifyDown(size_t index) {
    if (!isLeaf(index)) {
        T min_child_index = minChild(index);
        if (item[index] > item[min_child_index]) {
            std::swap(item[index], item[min_child_index]);
            heapifyDown(min_child_index);
        }
    }
}

template <typename T>
void Heap<T>::growArray() {
    T* new_item = new T[2 * capacity + 1];
    for (size_t i = 1; i <= capacity; i++)
        new_item[i] = item[i];

    capacity *= 2;
    delete[] item;
    item = new_item;

    std::cout << "Heap<T>::_growArray() increased array to capacity == " << capacity << std::endl;
}

template <typename T>
int Heap<T>::parent(size_t index) const { return index / 2; }

template <typename T>
int Heap<T>::minChild(size_t index) const {
    size_t left = index * 2;
    size_t right = index * 2 + 1;

    if (right > size) {
        return left;
    } else if (item[left] <= item[right]) {
        return left;
    } else {
        return right;
    }
}

template <typename T>
bool Heap<T>::isRoot(size_t index) const { return (index == 1); }

template <typename T>
bool Heap<T>::isLeaf(size_t index) const { return (index * 2 > size); }