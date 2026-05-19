#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <complex>
#include <string>
#include <iostream>

namespace alekseev {
  struct expected {
    std::string source;
  };

  std::istream & operator>>(std::istream & is, expected e);

  struct chr_lit {
    char data;

    bool operator<(const chr_lit & rhs) const;
  };

  std::istream & operator>>(std::istream & is, chr_lit & chr);
  std::ostream & operator<<(std::ostream & os, const chr_lit & chr);

  struct cmp_lsp {
    std::complex< double > data;

    bool operator<(const cmp_lsp & rhs) const;
  };

  std::istream & operator>>(std::istream & is, cmp_lsp & cmp);
  std::ostream & operator<<(std::ostream & os, const cmp_lsp & cmp);

  struct str_lit {
    std::string data;

    bool operator<(const str_lit & rhs) const;
  };

  std::istream & operator>>(std::istream & is, str_lit & str);
  std::ostream & operator<<(std::ostream & os, const str_lit & str);

  struct DataStruct {
    chr_lit key1;
    cmp_lsp key2;
    str_lit key3;

    bool operator<(const DataStruct & rhs) const;
  };

  std::istream & operator>>(std::istream & is, DataStruct & data);
  std::ostream & operator<<(std::ostream & os, const DataStruct & data);
}

#endif
