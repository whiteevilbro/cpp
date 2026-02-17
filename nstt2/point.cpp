#include "point.h"

#include "line.h"

#include <format>
#include <ostream>

bool Point::operator==(const Point& p) const {
  return (std::abs(x - p.x) < eps) && (std::abs(y - p.y) < eps);
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  return os << std::format("({}, {})", p.x, p.y);
}
