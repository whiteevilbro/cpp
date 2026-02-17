#ifndef LINE_H_
#define LINE_H_

#include "point.h"

#include <complex>
#include <ostream>

constexpr double eps = 1e-7;

class Line {
  friend std::ostream& operator<<(std::ostream& os, const Line& line);
  const double a_, b_, c_;

public:
  Line(const Point&, const Point&);
  Line(double a, double b, double c);

  Point operator&(const Line&) const;
  Line operator^(const Point&) const;
  bool operator==(const Line&) const;
};

#endif
