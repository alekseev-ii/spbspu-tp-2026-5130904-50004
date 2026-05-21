#include <functional>
#include "Polygon.h"
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iterator>
#include <map>
#include <sstream>
#include <iomanip>

namespace alekseev {
  using data_t = std::vector< Polygon >;
  using args_t = std::vector< std::string >;
  using size_t_command = std::function< size_t (const data_t &, const args_t &) >;

  double area(const data_t & data, const args_t & args);
  double extremum_area(const data_t & data, const args_t & args, bool max);
  double max_area(const data_t & data, const args_t & args);
  double min_area(const data_t & data, const args_t & args);
  size_t extremum_size(const data_t & data, const args_t & args, bool max);
  size_t max_size(const data_t & data, const args_t & args);
  size_t min_size(const data_t & data, const args_t & args);
  size_t count(const data_t & data, const args_t & args);
  size_t rects(const data_t & data, const args_t & args);
  size_t intersections(const data_t & data, const args_t & args);

  struct Exec {
    std::map< std::string, size_t_command > n_cmds;
    Exec();
    void operator()(const std::string & name, const data_t & data, const args_t & args);
  };
}

int main(int argc, char * argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " input_file\n";
    return 1;
  }
  std::ifstream ifs(argv[1]);
  if (!ifs) {
    std::cerr << "Error opening file " << argv[1] << "\n";
    return 1;
  }
  alekseev::data_t data;
  std::string line;
  while (std::getline(ifs, line)) {
    data.push_back(alekseev::from_string(line));
  }
  ifs.close();
  auto rem_it = std::remove_if(data.begin(), data.end(), [](const alekseev::Polygon & p) {
    return p.size() == 0;
  });
  data.erase(rem_it, data.end());

  alekseev::Exec exec;
  std::string command;
  std::cout << std::fixed << std::setprecision(2);
  while (std::getline(std::cin, command)) {
    std::istringstream iss(command);
    std::string name;
    iss >> name;
    std::istream_iterator< std::string > b(iss), e{};
    alekseev::args_t args;
    std::copy(b, e, std::back_inserter(args));
    try {
      exec(name, data, args);
    } catch (...) {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}

double alekseev::area(const data_t & data, const args_t & args)
{
  if (args.size() != 1) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  if (args[0] == "EVEN" || args[0] == "ODD") {
    bool odd = (args[0] == "ODD");
    std::vector< Polygon > temp;
    std::copy_if(data.begin(), data.end(), std::back_inserter(temp), [odd](const Polygon & x) {
      return (x.size() % 2 == 1) == odd;
    });
    return std::accumulate(temp.begin(), temp.end(), 0.0);
  } else if (args[0] == "MEAN") {
    if (data.empty()) {
      throw std::invalid_argument("Empty data");
    }
    double area = std::accumulate(data.begin(), data.end(), 0.0);
    return area / static_cast< double >(data.size());
  } else {
    try {
      size_t n = std::stoull(args[0]);
      if (n < 3) {
        throw std::invalid_argument("Wrong number of arguments");
      }
      data_t temp;
      std::copy_if(data.begin(), data.end(), std::back_inserter(temp), [n](const Polygon & x) {
        return x.size() == n;
      });
      return std::accumulate(temp.begin(), temp.end(), 0.0);
    } catch (...) {
      throw std::invalid_argument("Wrong argument");
    }
  }
}

double alekseev::extremum_area(const data_t & data, const args_t & args, bool max)
{
  if (args.size() != 1) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  if (data.empty()) {
    throw std::invalid_argument("Empty data");
  }
  int k = max ? 1 : -1;
  std::vector< double > squares;
  std::transform(data.begin(), data.end(), std::back_inserter(squares), [k](const Polygon & x) {
    return k * x.area();
  });
  return *std::max_element(squares.begin(), squares.end());
}

double alekseev::max_area(const data_t & data, const args_t & args)
{
  return extremum_area(data, args, true);
}

double alekseev::min_area(const data_t & data, const args_t & args)
{
  return extremum_area(data, args, false);
}

size_t alekseev::extremum_size(const data_t & data, const args_t & args, bool max)
{
  if (args.size() != 1) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  if (data.empty()) {
    throw std::invalid_argument("Empty data");
  }
  int k = max ? 1 : -1;
  std::vector< size_t > sizes;
  std::transform(data.begin(), data.end(), std::back_inserter(sizes), [k](const Polygon & x) {
    return k * x.size();
  });
  return *std::max_element(sizes.begin(), sizes.end());
}

size_t alekseev::max_size(const data_t & data, const args_t & args)
{
  return extremum_size(data, args, true);
}

size_t alekseev::min_size(const data_t & data, const args_t & args)
{
  return extremum_size(data, args, false);
}

size_t alekseev::count(const data_t & data, const args_t & args)
{
  if (args.size() != 1) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  if (args[0] == "EVEN" || args[0] == "ODD") {
    if (data.empty()) {
      return 0;
    }
    bool odd = args[0] == "ODD";
    return std::count_if(data.begin(), data.end(), [odd](const Polygon & x) {
      return (x.size() % 2 == 1) == odd;
    });
  } else {
    try {
      size_t n = std::stoull(args[0]);
      if (n < 3) {
        throw std::invalid_argument("Invalid vertex count");
      }
      if (data.empty()) {
        return 0;
      }
      return std::count_if(data.begin(), data.end(), [n](const Polygon & x) {
        return x.size() == n;
      });
    } catch (...) {
      throw std::invalid_argument("Wrong argument");
    }
  }
}

size_t alekseev::rects(const data_t & data, const args_t & args)
{
  if (!args.empty()) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  return std::count_if(data.begin(), data.end(), is_rectangle);
}

size_t alekseev::intersections(const data_t & data, const args_t & args)
{
  if (args.empty()) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  Polygon p(args);
  return std::count_if(data.begin(), data.end(), [p](const Polygon & x) {
    return x.intersects(p);
  });
}

alekseev::Exec::Exec()
{
  n_cmds["MAX"] = max_size;
  n_cmds["MIN"] = min_size;
  n_cmds["COUNT"] = count;
  n_cmds["INTERSECTIONS"] = intersections;
}

void alekseev::Exec::operator()(const std::string & name, const data_t & data, const args_t & args)
{
  IOGuard guard(std::cout);
  std::cout << std::fixed << std::setprecision(1);
  if (args.empty()) {
    if (name == "RECTS") {
      std::cout << rects(data, args) << "\n";
      return;
    }
  } else {
    if (name == "MAX" && args[0] == "AREA") {
      std::cout << max_area(data, args) << "\n";
      return;
    } else if (name == "MIN" && args[0] == "AREA") {
      std::cout << min_area(data, args) << "\n";
      return;
    } else if (name == "AREA") {
      std::cout << area(data, args) << "\n";
      return;
    } else {
      std::cout << n_cmds.at(name)(data, args) << "\n";
      return;
    }
  }
  throw std::invalid_argument("Wrong argument");
}
