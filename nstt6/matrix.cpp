#include "matrix.hpp"

#include "gtest/gtest.h"
#include <cstdio>
#include <vector>

TEST(MatrixTest, AddressTest) {
  Matrix<double> m = Matrix<double>(2, 1.0);

  ASSERT_EQ(m[0][0], 1.0);
  ASSERT_EQ(m[0][1], 0.0);
  m[0][1] = 2.0;
  ASSERT_EQ(m[0][1], 2.0);
}

TEST(MatrixTest, AddTest) {
  Matrix<double> m1 = Matrix<double>(2, 1.0);
  Matrix<double> m2 = Matrix<double>(2, 1.0);


  Matrix<double> m3 = m1 + m2;
  ASSERT_EQ(m3, Matrix<double>(2, 2.0));

  m1 += m2;
  ASSERT_EQ(m1, m3);
}

TEST(MatrixTest, MulTest) {
  Matrix<double> m1 = Matrix<double>(2, 2.0);
  Matrix<double> m2 = Matrix<double>(2, 2.0);


  Matrix<double> m3 = m1 * m2;
  ASSERT_EQ(m3, Matrix<double>(2, 4.0));

  m1 *= 2;
  ASSERT_EQ(m1, m3);
}

TEST(MatrixTest, CastTest) {
  Matrix<double> m1 = Matrix<double>(2, 2.0);
  m1[0][1]          = 1;

  ASSERT_EQ(static_cast<double>(m1), 5);
}

TEST(MatrixTest, VectorTest) {
  std::vector<double> v = {1, 2};
  Matrix<double> m1     = Matrix<double>(v);
  Matrix<double> m2     = Matrix<double>(2, 1);
  m2[1][1]              = 2;

  ASSERT_EQ(m1, m2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
