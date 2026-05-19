#include "Polygon.h"
#include <string>
#include <sstream>

std::istream & alekseev::operator>>(std::istream & is, expected e)
{
  if (!is) {
    return is;
  }
  char c = 0;
  for (size_t i = 0; i < e.source.length(); ++i) {
    is >> c;
    if (c != e.source[i]) {
      is.setstate(std::ios_base::failbit);
      return is;
    }
  }
  return is;
}

std::istream & alekseev::operator>>(std::istream & is, Point & p)
{
  if (!is) {
    return is;
  }
  is >> expected{"("} >> p.x >> expected{";"};
  is >> p.y >> expected{")"};
  return is;
}

std::istream & alekseev::operator>>(std::istream & is, Polygon & p)
{
  if (!is) {
    return is;
  }
  size_t n = 0;
  while (!is.eof()) {
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    iss >> n;
    p.points.resize(n);
    for (size_t i = 0; i < n; ++i) {
      iss >> p.points[i];
    }
    if (iss.good()) {
      break;
    }
  }
  return is;
}
