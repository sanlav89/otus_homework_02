#include <gtest/gtest.h>

#include "customcontainer.h"

TEST(CustomContainer, BasicAssertions)
{
    CustomContainer<int> v(10);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);
    v.push_back(10);
    v.push_back(11);
    v.push_back(12);

    EXPECT_EQ(v[2], 7);
    EXPECT_EQ(v.size(), 8);

    CustomContainer<int>::iterator it = v.begin();
    EXPECT_EQ(*it, 5);
    it++;
    EXPECT_EQ(*it, 6);

    v.push_back(13);
    it = v.end();
    v.push_back(14);

    EXPECT_EQ(*it, 14);
}

TEST(CustomContainerExtended, BasicAssertions)
{
    constexpr std::size_t map_size = 10;
    auto vector_std_alloc = CustomContainer<int>(map_size);
    for (auto i = 0u; i < 2 * map_size; i++) {
        vector_std_alloc.push_back(i);
    }

    for (auto i = 0u; i < 2 * map_size; i++) {
        EXPECT_EQ(vector_std_alloc[i], i);
    }
}
