#include "List.hpp"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <vector>

TEST(List, CreatingEmptyList) {
    std::vector<int> test_obj;
    List<int> box;
    ASSERT_EQ(test_obj.size(), box.size());
}

TEST(List, CreatingListWithValues) {
    std::vector<int> test_obj(10, 10);
    List<int> box(10, 10);
    for(size_t i = 0; i < test_obj.size(); ++i) ASSERT_EQ(test_obj[i], box[i]);
}

TEST(List, CreatingListWithCopy) {
    std::vector<int> test_obj(10, 10);
    List<int> box(10, 10);
    List<int> box_copy(box);
    for(size_t i = 0; i < test_obj.size(); ++i) ASSERT_EQ(test_obj[i], box_copy[i]);
}

TEST(List, CreatingListWithMoved) {
    std::vector<int> test_obj(10, 10);
    List<int> box(10, 10);
    List<int> box_copy(std::move(box));
    for(size_t i = 0; i < test_obj.size(); ++i) ASSERT_EQ(test_obj[i], box_copy[i]);
    EXPECT_EQ(box_copy.size(), test_obj.size());
    EXPECT_EQ(box.size(), 0);
}

TEST(List, Equal) {
    std::vector<int> test_obj(10, 10);
    List<int> box(10, 10);
    List<int> box_copy;
    box_copy = box;
    for(size_t i = 0; i < test_obj.size(); ++i) ASSERT_EQ(test_obj[i], box_copy[i]);
}

TEST(List, EqualMoved) {
    std::vector<int> test_obj(10, 10);
    List<int> box(10, 10);
    List<int> box_copy;
    box_copy = std::move(box);
    for(size_t i = 0; i < test_obj.size(); ++i) ASSERT_EQ(test_obj[i], box_copy[i]);
    EXPECT_EQ(box_copy.size(), test_obj.size());
    EXPECT_EQ(box.size(), 0);
}

TEST(List, PushBack) {
    std::vector<int> cor = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    List<int> box;
    for(size_t i = 0; i < 10; ++i) box.push_back(i);
    for(size_t i = 0; i < 10; ++i) ASSERT_EQ(cor[i], box[i]);
}

TEST(List, Size) {
    std::vector<int> cor = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    List<int> box;
    for(size_t i = 0; i < 10; ++i) box.push_back(i);
    ASSERT_EQ(cor.size(), box.size());
}

TEST(List, Erase) {
    std::vector<int> cor = {0, 1, 3, 5, 7, 8, 9};
    List<int> box;
    for(size_t i = 0; i < 10; ++i) box.push_back(i);
    box.erase(6);
    box.erase(4);
    box.erase(2);
    for(size_t i = 0; i < box.size(); ++i) ASSERT_EQ(cor[i], box[i]);
}

TEST(List, Insert) {
    std::vector<int> cor = {10, 0, 1, 3, 20, 5, 7, 8, 9, 30};
    List<int> box;
    box.push_back(0);
    box.push_back(1);
    box.push_back(3);
    box.push_back(5);
    box.push_back(7);
    box.push_back(8);
    box.push_back(9);
    // box = {0, 1, 2, 3, 5, 7, 8, 9};

    box.insert(10, 0);
    box.insert(20, box.size()/2);
    box.insert(30, box.size());
    for(size_t i = 0; i < box.size(); ++i) ASSERT_EQ(cor[i], box[i]);
}

TEST(List, IteratorBegin) {
    List<int> box(3, 3);
    for(size_t i = 0; i < box.size(); ++i) box[i] = i;
    ASSERT_EQ(box[0], *box.begin());
}

TEST(List, Iterators) {
    std::vector<int> storage, output = {0, 1, 2};
    List<int> box(3, 3);
    for(size_t i = 0; i < box.size(); ++i) box[i] = i;
    for(int& n : box) storage.push_back(n);
    ASSERT_EQ(storage, output);
}