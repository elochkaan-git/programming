#include "Box.hpp"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Box, CreatingEmptyBox) {
    std::vector<int> test_obj;
    Box<int> box;
    ASSERT_EQ(test_obj.size(), box.size());
}

TEST(Box, CreatingBoxWithCapacity) {
    std::vector<int> test_obj(10);
    Box<int> box(10);
    ASSERT_EQ(box.size(), 10);
}