#include <gtest/gtest.h>

#include "customcontainer.h"

// Demonstrate some basic assertions.
TEST(CustomContainer, BasicAssertions)
{
    CustomContainer<int> v;
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

    it = v.end();
    v.push_back(13);
    EXPECT_EQ(*it, 13);
}
