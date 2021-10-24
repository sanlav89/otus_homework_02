#include <iostream>
#include <map>
#include <vector>

#include "utils.h"

int main()
{
    std::cout << "Hello from CustomAllocator!" << std::endl;
    constexpr int map_size = 10;

    auto map_std = utils::map_std_alloc<int, int>{};
    utils::fill_map_by_factorial(map_std, map_size);
    utils::print_map(map_std);

//    std::cout << "\n\n\n\n****  next part ********\n\n\n\n" << std::endl;

    auto map_custom_allocator = utils::map_custom_alloc<int, int>{};
    utils::fill_map_by_factorial(map_custom_allocator, map_size);
    utils::print_map(map_custom_allocator);
//    int *a = static_cast<int *>(&map_custom_allocator.begin());

//    std::cout << "\n\n\n\n****  next part ********\n\n\n\n" << std::endl;

//    std::vector<int> vector_std;
//    std::vector<int, CustomAllocator<int>> vector;
//    for (int i = 0; i < map_size; ++i) {
//        vector.push_back(i);
//    }
//    for (const auto& v : vector) {
//        std::cout << v << ' ';
//    }
//    std::cout << std::endl;

//    std::cout << "\n\n\n\n****  next part ********\n\n\n\n" << std::endl;

//    auto other = vector;
//    for (const auto& v : other) {
//        std::cout << v << ' ';
//    }
//    std::cout << std::endl;

    return 0;
}
