#include "avl.h" // IWYU pragma: keep

#include "gtest/gtest.h"
#include <algorithm>
#include <vector>

std::vector<int> elems = {5, 1, 4, 3, 7, 2};

TEST(AvlTreeTest, TestMin) {
  AVLTree<int> tree;
  for (auto elem : elems) {
    tree.insert(elem);
  }
  ASSERT_TRUE(tree.min() == *std::min_element(elems.begin(), elems.end()));
}

TEST(AvlTreeTest, TextMax) {
  AVLTree<int> tree;
  for (auto elem : elems) {
    tree.insert(elem);
  }
  ASSERT_TRUE(tree.max() == *std::max_element(elems.begin(), elems.end()));
}

TEST(AvlTreeTest, TestRemove) {
  AVLTree<int> tree;
  for (auto elem : elems) {
    tree.insert(elem);
  }
  int min = tree.min();
  ASSERT_TRUE(min == *std::min_element(elems.begin(), elems.end()));
  tree.remove(min);
  elems.erase(std::find(elems.begin(), elems.end(), 2));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
