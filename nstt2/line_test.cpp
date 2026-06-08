#include "line.h"
#include "point.h"

#include "gtest/gtest.h"

TEST(LineTest, TestConstructorEquivalence) {
  Line l1 = Line::getLine(1, 1, 0).value();
  Line l2 = Line::getLine(Point(0, 0), Point(1, -1)).value();
  ASSERT_EQ(l1, l2);

  Line l3 = Line::getLine(-5, 3, 3).value();
  Line l4 = Line::getLine(Point(-3, -6), Point(3, 4)).value();
  ASSERT_EQ(l3, l4);
}

TEST(LineTest, TestScalarScaling) {
  Line l1 = Line::getLine(1, 1, 0).value();
  Line l2 = Line::getLine(2, 2, 0).value();
  Line l3 = Line::getLine(-24.5l, -24.5l, 0).value();
  ASSERT_EQ(l1, l2);
  ASSERT_EQ(l2, l3);
  ASSERT_EQ(l1, l3);
}

TEST(LineTest, TestIntersection) {
  Line l1 = Line::getLine(1, 1, 0).value();
  Line l2 = Line::getLine(1, -1, 0).value();
  ASSERT_EQ(l1 & l2, Point(0, 0));

  Line l3 = Line::getLine(-5, 3, 3).value();
  Line l4 = Line::getLine(3, 5, 39).value();
  ASSERT_EQ(l3 & l4, Point(-3, -6));
}

TEST(LineTest, TestPerpendicularThroughPointOnLine) {
  Line l1  = Line::getLine(1, 1, 0).value();
  Point p1 = Point(0, 0);
  Line h1  = Line::getLine(1, -1, 0).value();
  ASSERT_EQ(l1 ^ p1, h1);

  Line l2  = Line::getLine(-5, 3, 3).value();
  Point p2 = Point(-3, -6);
  Line h2  = Line::getLine(3, 5, 39).value();
  ASSERT_EQ(l2 ^ p2, h2);
}

TEST(LineTest, TestPerpendicularThroughAnyPoint) {
  Line l1  = Line::getLine(1, 1, 0).value();
  Point p1 = Point(1, 1);
  Line h1  = Line::getLine(1, -1, 0).value();
  ASSERT_EQ(l1 ^ p1, h1);

  Line l2  = Line::getLine(-5, 3, 3).value();
  Point p2 = Point(2, -9);
  Line h2  = Line::getLine(3, 5, 39).value();
  ASSERT_EQ(l2 ^ p2, h2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
