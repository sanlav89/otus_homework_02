#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <map>
#include <vector>
#include <iostream>

namespace utils {
    int factorial(const int &n)
    {
        return int(round(std::tgamma(n + 1)));
    }

    template<typename T, typename U>
    void fill_map_by_factorial(std::map<T, U> &map, const int &size)
    {
        for (auto i = 0; i < size; i++) {
            map.insert({i, factorial(i)});
        }
    }

    template<typename T, typename U>
    void print_map(const std::map<T, U> &map)
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
