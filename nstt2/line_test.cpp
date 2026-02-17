#include "line.h"
#include "point.h"

#include "gtest/gtest.h"

TEST(LineTest, TestConstructorEquivalence) {
  Line l1 = Line(1, 1, 0);
  Line l2 = Line(Point(0, 0), Point(1, -1));
  ASSERT_EQ(l1, l2);

  Line l3 = Line(-5, 3, 3);
  Line l4 = Line(Point(-3, -6), Point(3, 4));
  ASSERT_EQ(l3, l4);
}

TEST(LineTest, TestScalarScaling) {
  Line l1 = Line(1, 1, 0);
  Line l2 = Line(2, 2, 0);
  Line l3 = Line(-24.5l, -24.5l, 0);
  ASSERT_EQ(l1, l2);
  ASSERT_EQ(l2, l3);
  ASSERT_EQ(l1, l3);
}

TEST(LineTest, TestIntersection) {
  Line l1 = Line(1, 1, 0);
  Line l2 = Line(1, -1, 0);
  ASSERT_EQ(l1 & l2, Point(0, 0));

  Line l3 = Line(-5, 3, 3);
  Line l4 = Line(3, 5, 39);
  ASSERT_EQ(l3 & l4, Point(-3, -6));
}

TEST(LineTest, TestPerpendicularThroughPointOnLine) {
  Line l1  = Line(1, 1, 0);
  Point p1 = Point(0, 0);
  Line h1  = Line(1, -1, 0);
  ASSERT_EQ(l1 ^ p1, h1);

  Line l2  = Line(-5, 3, 3);
  Point p2 = Point(-3, -6);
  Line h2  = Line(3, 5, 39);
  ASSERT_EQ(l2 ^ p2, h2);
}

TEST(LineTest, TestPerpendicularThroughAnyPoint) {
  Line l1  = Line(1, 1, 0);
  Point p1 = Point(1, 1);
  Line h1  = Line(1, -1, 0);
  ASSERT_EQ(l1 ^ p1, h1);

  Line l2  = Line(-5, 3, 3);
  Point p2 = Point(2, -9);
  Line h2  = Line(3, 5, 39);
  ASSERT_EQ(l2 ^ p2, h2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
