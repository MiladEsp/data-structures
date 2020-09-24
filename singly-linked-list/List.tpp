#include "List.h"

/** 
 * Constructor for the List class
 * Initializes the head to nullptr
*/
template <typename T>
List<T>::List() : head_(nullptr) {}

/** 
 * Destructor for the List class
 * Frees the memory allocated to the ListNodes
*/
template <typename T>
List<T>::~List() {
    ListNode* thru = head_;

    while (thru != nullptr) {
        ListNode* to_be_deleted = thru;

        thru = thru->next;
        delete to_be_deleted;
        to_be_deleted = nullptr;
    }
}

// Constructor for the ListNode class
template <typename T>
List<T>::ListNode::ListNode(const T& data) : data(data), next(nullptr) {}

// Destructor for the ListNode class
template <typename T>
List<T>::ListNode::~ListNode() {}

// Overloaded [] operator for the List class
template <typename T>
const T& List<T>::operator[](unsigned index) const {
    ListNode* thru = head_;

    while (index > 0 && thru->next != nullptr) {
        thru = thru->next;
        index--;
    }

    return thru->data;
}

// insert a ListNode at the front of the List
template <typename T>
void List<T>::insertAtFront(const T& data) {
    ListNode* node = new ListNode(data);

    node->next = head_;
    head_ = node;
}

/**
 * Finds and returns the ListNode containing `data` in the
 * List or `nullptr` if the data is not found.
 */
template <typename T>
typename List<T>::ListNode* List<T>::find(const T& data) {
    ListNode* thru = head_;
    while (thru != nullptr) {
        if (thru->data == data) {
            return thru;
        }
        thru = thru->next;
    }
    return nullptr;
}