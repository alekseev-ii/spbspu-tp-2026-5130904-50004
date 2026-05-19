#ifndef POLYGON_H
#define POLYGON_H
#include <string>
#include <vector>
#include <iostream>

namespace alekseev {
  struct Point {
    int x, y;
  };

  std::istream & operator>>(std::istream & is, Point & p);

  struct Polygon {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & is, Polygon & p);
}

#endif
