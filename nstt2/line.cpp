#include "line.h"

#include "point.h"

#include <format>
#include <limits>
#include <ostream>

Line::Line(const Point& p1, const Point& p2):
    a_(p2.y - p1.y), b_(p1.x - p2.x), c_(p1.y * p2.x - p1.x * p2.y) {}

Line::Line(double a, double b, double c):
    a_(a), b_(b), c_(c) {}

Point Line::operator&(const Line& line) const {
  double denom = line.a_ * b_ - a_ * line.b_;
  if (denom < eps) {
    return Point(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
  }
  return Point((line.b_ * c_ - b_ * line.c_) / denom, (a_ * line.c_ - line.a_ * c_) / denom);
}

Line Line::operator^(const Point& p) const {
  return Line(b_, -a_, a_ * p.y - b_ * p.x);
}

bool Line::operator==(const Line& line) const {
  double k;
  if (!(std::abs(line.a_) < eps)) {
    k = a_ / line.a_;
  } else if (!(std::abs(line.b_) < eps)) {
    k = b_ / line.b_;
  } else if (!(std::abs(line.c_) < eps)) {
    k = c_ / line.c_;
  } else {
    return (std::abs(a_) < eps && std::abs(b_) < eps && std::abs(c_));
  }
  return (std::abs(a_ - k * line.a_) < eps) && (std::abs(b_ - k * line.b_) < eps) && (std::abs(c_ - k * line.c_) < eps);
}

std::ostream& operator<<(std::ostream& os, const Line& line) {
  return os << std::format("({}, {}, {})", line.a_, line.b_, line.c_);
}
