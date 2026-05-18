#include "DataStruct.h"

std::istream & alekseev::operator>>(std::istream & is, expected e)
{
  if (!is) {
    return is;
  }
  char c = 0;
  is >> c;
  if (c != e.c) {
    is.setstate(std::ios_base::failbit);
  }
  return is;
}

std::istream & alekseev::operator>>(std::istream & is, chr_lit & chr)
{
  if (!is) {
    return is;
  }
  char c = 0;
  is >> expected{'\''} >> c >> expected{'\''};
  return is;
}
