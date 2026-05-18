#include "DataStruct.h"

std::istream & alekseev::operator>>(std::istream & is, expected e)
{
  if (!is) {
    return is;
  }
  char c = 0;
  is >> c;
  for (size_t i = 0; i < e.source.length(); ++i) {
    if (c != e.source[i]) {
      is.setstate(std::ios_base::failbit);
      return is;
    }
    is >> c;
  }
  return is;
}

std::istream & alekseev::operator>>(std::istream & is, chr_lit & chr)
{
  if (!is) {
    return is;
  }
  is >> expected{"\'"} >> chr.data >> expected{"\'"};
  return is;
}
