#include "DataStruct.h"

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
  is >> expected{"#c("} >> r >> i >> expected{")"};
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
  str = {res};
  return is;
}

std::ostream & alekseev::operator<<(std::ostream & os, const str_lit & str)
{
  os << "\"" << str.data << "\"";
  return os;
}

bool alekseev::DataStruct::operator<(const DataStruct & rhs) const
{
  if (key1 < rhs.key1) {
    return true;
  }
  if (key2 < rhs.key2 && !(rhs.key1 < key1)) {
    return true;
  }
  if (key3 < rhs.key3 && !(rhs.key2 < key2) && !(rhs.key1 < key1)) {
    return true;
  }
  return false;
}

std::istream & alekseev::operator>>(std::istream & is, DataStruct & data)
{
  if (!is) {
    return is;
  }
  while (!is.eof()) {
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    bool was[3]{false};
    char n = 0;
    iss >> expected{"("};
    for (size_t i = 0; i < 3; ++i) {
      iss >> expected{":key"} >> n;
      if (n == '1') {
        if (was[0]) {
          continue;
        }
        was[0] = true;
        iss >> data.key1;
      } else if (n == '2') {
        if (was[1]) {
          continue;
        }
        was[1] = true;
        iss >> data.key2;
      } else if (n == '3') {
        if (was[2]) {
          continue;
        }
        was[2] = true;
        iss >> data.key3;
      } else {
        continue;
      }
    }
    iss >> expected{":)"};
    if (iss.fail()) {
      continue;
    }
    break;
  }
  return is;
}

std::ostream & alekseev::operator<<(std::ostream & os, const DataStruct & data)
{
  os << "(:key1 " << data.key1 << ":key2 " << data.key2 << ":key3 " << data.key3 << ":)";
  return os;
}
