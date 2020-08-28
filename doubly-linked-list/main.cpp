#include <iostream>
#include "LinkedList.h"

int main()
{
    LinkedList<int> list;

    list.pushBack(5);
    list.pushBack(2);
    list.pushFront(1);
    list.pushFront(100);
    list.pushBack(10);

    std::cout << "Size of the linked list: " << list.size() << std::endl;
    std::cout << "Front element of the linked list: " << list.front() << std::endl;
    std::cout << "Back element of the linked list: " << list.back() << std::endl;
    std::cout << "------------------------" << std::endl;
    
    list.popBack();
    list.popFront();

    std::cout << "Size of the linked list: " << list.size() << std::endl;
    std::cout << "Front element of the linked list: " << list.front() << std::endl;
    std::cout << "Back element of the linked list: " << list.back() << std::endl;
    std::cout << "Linked list is empty (0: false, 1: true)? " << list.empty() << std::endl;

    return 0;
}