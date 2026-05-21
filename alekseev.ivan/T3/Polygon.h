#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>

namespace alekseev {
  struct Point {
    int x, y;

    Point operator+(const Point & other) const;
    Point operator-(const Point & other) const;
    bool operator==(const Point & other) const;
  };

  bool less_angle(const Point & a, const Point & b, double xc, double yc);
  Point point_from_string(const std::string & s);
  std::istream & operator>>(std::istream & is, Point & p);
  std::ostream & operator<<(std::ostream & os, const Point & p);
  int cross(const Point & o, const Point & a, const Point & b);
  bool onSegment(const Point & p, const Point & a, const Point & b);
  bool segmentsIntersect(const Point & a, const Point & b, const Point & c, const Point & d);

  struct Polygon {
    std::vector< Point > points_;
    Polygon();
    explicit Polygon(const std::vector< Point > & points);
    explicit Polygon(const std::vector< std::string > & args);

    double area() const;
    size_t size() const;
    double operator+(const Polygon & other) const;
    bool is_inner(const Point & p) const;
    bool intersects(const Polygon & other) const;
  };

  double operator+(double a, const Polygon & b);
  std::istream & operator>>(std::istream & is, Polygon & p);
  Polygon from_string(const std::string & s);
  bool is_rectangle(const Polygon & p);

  struct expected {
    std::string source;
  };

  std::istream & operator>>(std::istream & is, expected e);

  struct IOGuard {
    explicit IOGuard(std::basic_ios< char > & stream);
    ~IOGuard();

    private:
      std::basic_ios< char > & stream_;
      std::streamsize precision_;
      std::streamsize width_;
      std::basic_ios< char >::fmtflags flags_;
      char fill_;
  };
}

#endif
