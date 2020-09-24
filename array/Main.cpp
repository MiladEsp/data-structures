#include <cstring>
#include <iostream>

#include "Array.h"

int main() {
    // An example of the use of our Array class

    Array<int, 5> data;

    Array<std::string, data.Size()> newArray;

    std::memset(data.Data(), 0, data.Size() * sizeof(int));

    for (size_t i = 0; i < data.Size(); i++) {
        data[i] = 2;
        std::cout << data[i] << std::endl;
    }

    return 0;
}