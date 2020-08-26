#include <iostream>
#include "List.h"

int main()
{
    List<int> list;

    int item_a = 5;
    int item_b = 30;

    std::cout << "Inserting element 5 at front..." << std::endl;
    list.insertAtFront(item_a);
    std::cout << "list[0]: " << list[0] << std::endl;

    std::cout << "Inserting element 30 at front..." << std::endl;
    list.insertAtFront(item_b);
    std::cout << "list[0]: " << list[0] << std::endl;
    std::cout << "list[1]: " << list[1] << std::endl;

    return 0;
}