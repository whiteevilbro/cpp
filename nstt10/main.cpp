#include "limited.hpp"

#include "gtest/gtest.h"
#include <stdexcept>

class Two: Limited<Two, 2> {
};

TEST(LimTest, TestCtr) {
  Two one;
  Two two;

  ASSERT_THROW(Two(), std::runtime_error);
}

TEST(LimTest, TestCopyCtr) {
  Two one;
  Two two;

  ASSERT_THROW((Two(one)), std::runtime_error);
}

TEST(LimTest, TestMoveCtr) {
  Two one;
  Two two;

  ASSERT_THROW((Two(std::move(one))), std::runtime_error);
}

TEST(LimTest, Destruct) {
  { Two one; }
  Two two;

  ASSERT_NO_THROW(Two());
}

TEST(LimTest, TestCopyAssign) {
  Two one;
  Two two;

  ASSERT_NO_THROW(two = one);
}

TEST(LimTest, TestMoveAssign) {
  Two one;
  Two two;

  ASSERT_NO_THROW(two = std::move(one));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
