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

bool alekseev::chr_lit::operator<(const chr_lit & rhs) const
{
  return data < rhs.data;
}

std::istream & alekseev::operator>>(std::istream & is, chr_lit & chr)
{
  if (!is) {
    return is;
  }
  is >> expected{"\'"} >> chr.data >> expected{"\'"};
  return is;
}

std::ostream & alekseev::operator<<(std::ostream & os, const chr_lit & chr)
{
  os << "\'" << chr.data << "\'";
  return os;
}

bool alekseev::cmp_lsp::operator<(const cmp_lsp & rhs) const
{
  return std::abs(data) < std::abs(rhs.data);
}

std::istream & alekseev::operator>>(std::istream & is, cmp_lsp & cmp)
{
  if (!is) {
    return is;
  }
  double r = 0, i = 0;
  is >> expected{"#c("} >> r >> expected{" "} >> i >> expected{")"};
  cmp = {std::complex< double >(r, i)};
  return is;
}

std::ostream & alekseev::operator<<(std::ostream & os, const cmp_lsp & cmp)
{
  os << "#c(" << cmp.data.real() << " " << cmp.data.imag() << ")";
  return os;
}

bool alekseev::str_lit::operator<(const str_lit & rhs) const
{
  return data.size() < rhs.data.size();
}

std::istream & alekseev::operator>>(std::istream & is, str_lit & str)
{
  if (!is) {
    return is;
  }
  std::string res;
  is >> expected{"\""};
  std::getline(is, res, '\"');
  is >> expected{"\""};
  str = {res};
  return is;
}

std::ostream & alekseev::operator<<(std::ostream & os, const str_lit & str)
{
  os << "\"" << str.data << "\"";
  return os;
}

std::istream & alekseev::operator>>(std::istream & is, DataStruct & data)
{
  if (!is) {
    return is;
  }
  char n = 0;
  is >> expected{"("};
  for (size_t i = 0; i < 3; ++i) {
    is >> expected{":key"} >> n >> expected{" "};
    switch (n) {
      case '1': is >> data.key1;
        break;
      case '2': is >> data.key2;
        break;
      case '3': is >> data.key3;
        break;
      default: is.setstate(std::ios_base::failbit);
        return is;
    }
  }
  return is;
}

std::ostream & alekseev::operator<<(std::ostream & os, const DataStruct & data)
{
  os << "(:key1 " << data.key1 << ":key2 " << data.key2 << ":key3)";
  return os;
}
