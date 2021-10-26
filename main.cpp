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

    auto vector_std = std::vector<int, utils::c_alloc_vec<int>>{};
    auto vector_custom = CustomContainer<int, utils::c_alloc_vec<int>>{};

    for (auto i = 0u; i < map_size; i++) {
        vector_std.push_back(i);
        vector_custom.push_back(i);
    }

    utils::print_vector(vector_std);
    utils::print_vector(vector_custom);

    return 0;
}
