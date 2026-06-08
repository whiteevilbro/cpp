#include "gtest/gtest.h"

// template<typename Checker, typename... Args>
// int getIndexOfFirstMatch(Checker check, Args... args) {
//   auto l = [n = -1, i = 0, &check](auto x) mutable {
//     if (n >= 0)
//       return n;
//     if (check(x)) {
//       n = i;
//       return n;
//     }
//     i++;
//     return -1;
//   };
//   return (l(args), ...);
// }

// template<typename Checker, typename... Args>
// int getIndexOfFirstMatch(Checker check, Args... args) {
//   auto l = [n = -1, i = 0, &check](auto&& x) mutable { return n >= 0 ? n : (check(x) ? n = i : i++, -1); };
//   return (l(std::forward<Args>(args)), ...);
// }

template<typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker check, Args... args) {
  int n  = -1;
  auto l = [&n, &check](auto&& x) { return n++, !check(x); };
  return (l(std::forward<Args>(args)) && ...) ? -1 : n;
}

TEST(CheckTest, CorrectnessTest) {
  auto isEven = [](int n) { return !static_cast<bool>(n & 1); };
  EXPECT_EQ(2, getIndexOfFirstMatch(isEven, 17, 47, 30, 59, 39));
  EXPECT_EQ(0, getIndexOfFirstMatch(isEven, 44, 34, 57, 27, 88));
  EXPECT_EQ(1, getIndexOfFirstMatch(isEven, 89, 32, 52, 77, 62));
  EXPECT_EQ(-1, getIndexOfFirstMatch(isEven, 85, 53, 77, 69, 45));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
