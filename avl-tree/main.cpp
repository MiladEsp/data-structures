#include <string>
#include <vector>

#include "AVL.h"

int main() {
    const int V_SIZE = 1000;

    if (V_SIZE < 100)
        throw std::runtime_error("Please set V_SIZE to at least 100");

    std::vector<int> int_storage(V_SIZE, 0);

    for (int i = 0; i < V_SIZE; i++) {
        int_storage[i] = i;
    }

    std::vector<std::string> string_storage(V_SIZE);
    for (int i = 0; i < V_SIZE; i++) {
        string_storage[i] = std::to_string(i);
    }

    {
        std::cout << "\nCreating AVL tree now..." << std::endl;
        AVL<int, std::string> t;

        std::cout << std::boolalpha;
        const bool empty_at_beginning = t.empty();
        std::cout << "AVL tree empty at the beginning? " << empty_at_beginning << std::endl;
        if (!empty_at_beginning) {
            throw std::runtime_error("Error: empty() should have been true at the beginning");
        }

        std::cout << "Inserting items..." << std::endl;

        t.insert(int_storage[37], string_storage[37]);
        t.insert(int_storage[19], string_storage[19]);
        t.insert(int_storage[51], string_storage[51]);
        t.insert(int_storage[55], string_storage[55]);
        t.insert(int_storage[4], string_storage[4]);
        t.insert(int_storage[11], string_storage[11]);
        t.insert(int_storage[20], string_storage[20]);
        t.insert(int_storage[2], string_storage[2]);
        t.insert(int_storage[3], string_storage[3]);
        t.insert(int_storage[5], string_storage[5]);
        t.insert(int_storage[6], string_storage[6]);
        t.insert(int_storage[7], string_storage[7]);
        t.insert(int_storage[17], string_storage[17]);
        t.insert(int_storage[67], string_storage[67]);
        t.insert(int_storage[66], string_storage[66]);

        const bool empty_after_insertions = t.empty();
        std::cout << "AVL tree empty after insertions? " << empty_after_insertions << std::endl;
        if (empty_after_insertions) {
            throw std::runtime_error("Error: empty() should have been false after insertions");
        }

        std::cout << "\nUsing find to show that 51 has been inserted:" << std::endl;
        std::cout << "t.find(51): " << t.find(51) << std::endl;

        std::cout << "\nTrying to remove some items:" << std::endl;
        std::cout << "t.remove(11): " << t.remove(11) << std::endl;
        std::cout << "t.remove(51): " << t.remove(51) << std::endl;
        std::cout << "t.remove(19): " << t.remove(19) << std::endl;
        std::cout << "t.remove(6): " << t.remove(6) << std::endl;
        std::cout << "t.remove(67): " << t.remove(67) << std::endl;
        std::cout << "t.remove(66): " << t.remove(66) << std::endl;
        std::cout << "t.remove(17): " << t.remove(17) << std::endl;

        try {
            std::cout << std::endl;
            std::cout << "Attempting to find a non-existent item, 51: " << std::endl;
            std::cout << "t.find(51): " << t.find(51);
            std::cout << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "(OK) Caught example exception with the following message:" << std::endl
                      << "\"" << e.what() << "\"" << std::endl;
        }

        try {
            std::cout << std::endl;
            std::cout << "Attempting to remove a non-existent item, 99: " << std::endl;
            std::cout << "t.remove(99): " << t.remove(99);
            std::cout << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "(OK) Caught example exception with the following message:" << std::endl
                      << "\"" << e.what() << "\"" << std::endl;
        }

        std::cout << "\nAVL tree will go out of scope and be destroyed now."
                  << "\n(All nodes will be removed...)\n";
    }

    std::cout << "\nSUCCESS - The program is exiting normally." << std::endl;

    return 0;
}
