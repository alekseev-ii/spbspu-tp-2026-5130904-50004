#include <vector>
#include "DataStruct.h"
#include <iterator>
#include <algorithm>

int main()
{
  std::vector< alekseev::DataStruct > data;
  std::istream_iterator< alekseev::DataStruct > begin(std::cin), end{};
  std::copy(begin, end, std::back_inserter(data));

  std::sort(data.begin(), data.end());

  std::ostream_iterator< alekseev::DataStruct > out(std::cout, "\n");
  std::copy(data.begin(), data.end(), out);
}
