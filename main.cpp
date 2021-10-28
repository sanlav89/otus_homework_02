#include <iostream>
#include <map>
#include <vector>
#include "utils.h"

int main()
{
    std::cout << "Hello from CustomAllocator!" << std::endl;
    constexpr std::size_t map_size = 10;

    auto map_alloc_std = std::map<int, int>{};
    auto map_alloc_custom =
            std::map<int, int, std::less<int>, utils::c_alloc_map<int, int>>{};

    for (auto i = 0u; i < map_size; i++) {
        map_alloc_std.insert({i, utils::factorial(i)});
        map_alloc_custom.insert({i, utils::factorial(i)});
    }

    utils::print_map(map_alloc_std);
    utils::print_map(map_alloc_custom);

    auto vector_std_alloc = CustomContainer<int>{};
    auto vector_custom_alloc = CustomContainer<int, utils::c_alloc_vec<int>, 10>{};

    for (auto i = 0u; i < map_size; i++) {
        vector_std_alloc.push_back(i);
        vector_custom_alloc.push_back(i);
    }

    utils::print_vector(vector_std_alloc);
    utils::print_vector(vector_custom_alloc);

    return 0;
}
