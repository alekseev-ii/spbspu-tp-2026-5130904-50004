#include "Shape.h"
#include <memory>
#include <iostream>
#include <iomanip>

namespace alekseev {
  void scale_pivot(std::weak_ptr< iShape > shape, point_t pivot, double k);
  std::shared_ptr< iShape > make_shape(Shapes sh);
  std::ostream & print_shapes(std::ostream & out, std::shared_ptr< alekseev::iShape > * shapes,
      size_t N);
}

int main()
{
  const size_t N = 3;
  std::shared_ptr< alekseev::iShape > shapes[N]{
    alekseev::make_shape(alekseev::RECTANGLE),
    alekseev::make_shape(alekseev::CIRCLE),
    alekseev::make_shape(alekseev::POLYGON)
  };
  double x = 0, y = 0, k = 2;
  // std::cin >> x >> y >> k;
  if (std::cin.fail() || k < 0) {
    std::cerr << "bad input\n";
    return 1;
  }

  print_shapes(std::cout, shapes, N);
  std::cout << "\n\n";
  for (size_t i = 0; i < N; i++) {
    alekseev::scale_pivot(shapes[i], alekseev::point_t{x, y}, k);
  }
  print_shapes(std::cout, shapes, N);
}

void alekseev::scale_pivot(std::weak_ptr< iShape > shape, point_t pivot, double k)
{
  if (k == 1) {
    return;
  }
  if (std::shared_ptr< iShape > locked_shape = shape.lock()) {
    locked_shape->scale(k);
    point_t center = locked_shape->getFrameRect().pos_;
    double x = k * center.x_ - (k - 1) * pivot.x_;
    double y = k * center.y_ - (k - 1) * pivot.y_;
    locked_shape->move(point_t{x, y});
  }
}

std::shared_ptr< alekseev::iShape > alekseev::make_shape(Shapes sh)
{
  if (sh == RECTANGLE) {
    return std::make_shared< Rectangle >(4, 4, point_t{3, 3});
  } else if (sh == CIRCLE) {
    return std::make_shared< Circle >(2, point_t{2, 2});
  } else if (sh == POLYGON) {
    point_t points[]{point_t{2, 2}, point_t{0, 2}, point_t{0, 0}, point_t{2, 0}};
    return std::make_shared< Polygon >(points, 4);
  } else {
    return nullptr;
  }
}

std::ostream & alekseev::print_shapes(std::ostream & out,
    std::shared_ptr< iShape > * shapes, size_t N)
{
  double sum_area = 0;
  double min_x, min_y, max_x, max_y;
  bool is_initialized = false;
  for (size_t i = 0; i < N; ++i) {
    double area = shapes[i]->getArea();
    alekseev::rectangle_t rect = shapes[i]->getFrameRect();
    out << "S: " << std::setw(10) << area << " ";
    out << "R: " << rect << "\n";
    sum_area += area;

    double x0 = rect.pos_.x_ - rect.width_ / 2;
    min_x = is_initialized ? (x0 < min_x ? x0 : min_x) : x0;
    double y0 = rect.pos_.y_ - rect.height_ / 2;
    min_y = is_initialized ? (y0 < min_y ? y0 : min_y) : y0;
    double x1 = rect.pos_.x_ + rect.width_ / 2;
    max_x = is_initialized ? (x1 > max_x ? x1 : max_x) : x1;
    double y1 = rect.pos_.y_ + rect.height_ / 2;
    max_y = is_initialized ? (y1 > max_y ? y1 : max_y) : y1;
    is_initialized = true;
  }
  out << "\tS: " << std::setw(10) << sum_area << " ";
  point_t center{(max_x + min_x) / 2.0, (max_y + min_y) / 2.0};
  out << "R: " << rectangle_t{max_x - min_x, max_y - min_y, center} << "\n";
  return out;
}
