#include <iostream>
#include <vector>
#include "customallocator.h"

int main()
{
    std::cout << "Hello World!" << std::endl;

    std::vector<int, CustomAllocator<int>> vector;

    for (int i = 0; i < 10; ++i) {
        vector.push_back(i);
    }

    for (const auto& v : vector) {
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    auto other = vector;

    for (const auto& v : other) {
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    return 0;
}
