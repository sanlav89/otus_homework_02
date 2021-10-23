#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include "customallocator.h"

namespace utils {

    template<typename T, typename U>
    using map_custom_alloc = std::map<T, U, std::less<int>, CustomAllocator<std::pair<const int, int>>>;

    template<typename T, typename U>
    using map_std_alloc = std::map<T, U>;

    int factorial(const int &n)
    {
        return int(round(std::tgamma(n + 1)));
    }

    template<typename T, typename U>
    void fill_map_by_factorial(map_custom_alloc<T, U> &map, const int &size)
    {
        for (auto i = 0; i < size; i++) {
            map.insert({i, factorial(i)});
        }
    }

    template<typename T, typename U>
    void fill_map_by_factorial(map_std_alloc<T, U> &map, const int &size)
    {
        for (auto i = 0; i < size; i++) {
            map.insert({i, factorial(i)});
        }
    }

    template<typename T, typename U>
    void print_map(const map_custom_alloc<T, U> &map)
    {
        for (const auto &item : map) {
            std::cout << item.first << " " << item.second << std::endl;
        }
    }

    template<typename T, typename U>
    void print_map(const map_std_alloc<T, U> &map)
    {
        for (const auto &item : map) {
            std::cout << item.first << " " << item.second << std::endl;
        }
    }

//    template<typename T>
//    void fillVectorByCounter(std::vector<T> &v, const int &size)
//    {
//        for (auto i = 0; i < size; i++) {
//            v.push_back(i);
//        }
//    }

//    template<typename T>
//    void printVector(const std::vector<T> &v)
//    {
//        for (auto value : v) {
//            std::cout << value << std::endl;
//        }
//    }
}

#endif // UTILS_H
