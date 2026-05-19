#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>

namespace alekseev {
  struct expected {
    std::string source;
  };

  std::istream & operator>>(std::istream & is, expected e);

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
