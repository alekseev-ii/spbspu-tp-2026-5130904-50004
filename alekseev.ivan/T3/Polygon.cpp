#include "Polygon.h"

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
