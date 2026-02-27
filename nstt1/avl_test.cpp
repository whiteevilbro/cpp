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
  ASSERT_EQ(tree.min(), *std::min_element(elems.begin(), elems.end()));
}

TEST(AvlTreeTest, TextMax) {
  AVLTree<int> tree;
  for (auto elem : elems) {
    tree.insert(elem);
  }
  ASSERT_EQ(tree.max(), *std::max_element(elems.begin(), elems.end()));
}

TEST(AvlTreeTest, TestRemove) {
  AVLTree<int> tree;
  for (auto elem : elems) {
    tree.insert(elem);
  }
  int min = tree.min();
  ASSERT_TRUE(min == *std::min_element(elems.begin(), elems.end()));
  tree.remove(min);
  std::vector<int> copyElem = elems;
  copyElem.erase(std::min_element(copyElem.begin(), copyElem.end()));
  ASSERT_EQ(tree.min(), *std::min_element(copyElem.begin(), copyElem.end()));
}

TEST(AvlTreeTest, TestCopy) {
  AVLTree<int> tree;
  for (auto elem : elems) {
    tree.insert(elem);
  }
  AVLTree<int> newTree = tree;
  tree.remove(tree.min());
  ASSERT_EQ(newTree.min(), *std::min_element(elems.begin(), elems.end()));
}

TEST(AvlTreeTest, TestCopyAssignment) {
  AVLTree<int> tree;
  for (auto elem : elems) {
    tree.insert(elem);
  }
  AVLTree<int> newTree;
  newTree.insert(*std::max_element(elems.begin(), elems.end()) + 1);
  newTree = tree;
  ASSERT_EQ(newTree.max(), *std::max_element(elems.begin(), elems.end()));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
