#ifndef POINT_H_
#define POINT_H_

struct Point {
  const double x;
  const double y;

  bool operator==(const Point&) const;
};

#endif
