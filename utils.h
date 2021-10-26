#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include "customallocator.h"
#include "customcontainer.h"

namespace utils {

    template<typename T, typename U, std::size_t BlockSize = 10>
    using c_alloc_map = CustomAllocator<std::pair<T, U>, BlockSize>;

    template<typename T>
    using c_alloc_vec = CustomAllocator<T>;

    int factorial(const int &n)
    {
        return int(round(std::tgamma(n + 1)));
    }

    template<typename T, typename U>
    void print_map(const std::map<T, U> &map)
    {
        std::cout << "std::map with default allocator: " << std::endl;
        for (const auto &item : map) {
            std::cout << item.first << " " << item.second << std::endl;
        }
    }

    template<typename T, typename U>
    void print_map(const std::map<T, U, std::less<T>, c_alloc_map<T, U>> &map)
    {
        std::cout << "std::map with custom allocator: " << std::endl;
        for (const auto &item : map) {
            std::cout << item.first << " " << item.second << std::endl;
        }
    }

    template<typename T>
    void print_vector(const std::vector<T, c_alloc_vec<T>> &v)
    {
        std::cout << "std::vector with custom allocator: " << std::endl;
        for (auto value : v) {
            std::cout << value << std::endl;
        }
    }

    template<typename T>
    void print_vector(const CustomContainer<T, c_alloc_vec<T>> &v)
    {
        std::cout << "custom vector with custom allocator: " << std::endl;
        for (auto it = v.begin(); it != v.end(); it++) {
            std::cout << *it << std::endl;
        }
    }

}

#endif // UTILS_H
