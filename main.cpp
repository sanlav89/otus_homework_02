#include <iostream>
#include <map>
#include <vector>

#include "customallocator.h"
#include "utils.h"

int main()
{
    std::cout << "Hello from CustomAllocator!" << std::endl;
    constexpr int map_size = 10;

    std::map<int, int> map_std;
    utils::fill_map_by_factorial(map_std, map_size);
//    std::map<int, int, CustomAllocsator<int>> map_custom_allocator;
    std::map<int, int> map_custom_allocator;
    utils::fill_map_by_factorial(map_custom_allocator, map_size);
    utils::print_map(map_custom_allocator);

//    std::vector<int> vector_std;
//    std::vector<int, CustomAllocator<int>> vector;
//    for (int i = 0; i < 10; ++i) {
//        vector.push_back(i);
//    }
//    for (const auto& v : vector) {
//        std::cout << v << ' ';
//    }
//    std::cout << std::endl;
//    auto other = vector;
//    for (const auto& v : other) {
//        std::cout << v << ' ';
//    }
//    std::cout << std::endl;

    return 0;
}
