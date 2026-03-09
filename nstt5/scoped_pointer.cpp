#include "copying_scoped_pointer.h"  // IWYU pragma: keep
#include "transfer_scoped_pointer.h" // IWYU pragma: keep

#include "gtest/gtest.h"

TEST(CopyTest, CorrectnessTest) {
  int* raw                          = new int(42);
  CopyingScopedPointer<int> managed = raw;

  ASSERT_EQ(*raw, *managed);
  *raw = 16;
  ASSERT_EQ(*raw, *managed);
  *managed = 32;
  ASSERT_EQ(*raw, *managed);
}

TEST(CopyTest, CopyingConstructorTest) {
  CopyingScopedPointer<int> managed_one = new int(42);
  CopyingScopedPointer<int> managed_two = managed_one;

  ASSERT_EQ(*managed_one, *managed_two);
  *managed_one = 16;
  ASSERT_NE(*managed_one, *managed_two);
}

TEST(CopyTest, CopyingAssignmentTest) {
  CopyingScopedPointer<int> managed_one = new int(42);
  CopyingScopedPointer<int> managed_two = nullptr;

  managed_two = managed_one;

  ASSERT_EQ(*managed_one, *managed_two);
  *managed_one = 16;
  ASSERT_NE(*managed_one, *managed_two);
}

// ======

TEST(TransferTest, CorrectnessTest) {
  int* raw                           = new int(42);
  TransferScopedPointer<int> managed = raw;

  ASSERT_EQ(*raw, *managed);
  *raw = 16;
  ASSERT_EQ(*raw, *managed);
  *managed = 32;
  ASSERT_EQ(*raw, *managed);
}

TEST(TransferTest, TransferConstructorTest) {
  TransferScopedPointer<int> managed_one = new int(42);
  ASSERT_EQ(*managed_one, 42);

  TransferScopedPointer<int> managed_two = std::move(managed_one);
  ASSERT_EQ(*managed_two, 42);
  // can't really test for UB, even if we were set managed_one to null in move ctr, i've found no way to catch it without changing inner behaviour
}

TEST(TransferTest, TransferAssignmentTest) {
  TransferScopedPointer<int> managed_one = new int(42);
  TransferScopedPointer<int> managed_two = nullptr;

  managed_two = std::move(managed_one);

  ASSERT_EQ(*managed_two, 42);
  // same as TransferConstructorTest
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
