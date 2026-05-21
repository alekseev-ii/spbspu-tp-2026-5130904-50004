#include "Shape.h"

std::ostream & alekseev::operator<<(std::ostream & out, const point_t & p)
{
  out << "(" << p.x_ << ", " << p.y_ << ")";
  return out;
}

std::ostream & alekseev::operator<<(std::ostream & out, const rectangle_t & r)
{
  out << r.width_ << " " << r.height_ << " " << r.pos_;
  return out;
}

alekseev::Rectangle::Rectangle(double width, double height, point_t pos):
  rect_(rectangle_t{width, height, pos})
{
}

double alekseev::Rectangle::getArea() const
{
  return rect_.height_ * rect_.width_;
}

alekseev::rectangle_t alekseev::Rectangle::getFrameRect() const
{
  return rect_;
}

void alekseev::Rectangle::move(point_t new_center)
{
  rect_.pos_ = new_center;
}

void alekseev::Rectangle::move(double x, double y)
{
  rect_.pos_.x_ += x;
  rect_.pos_.y_ += y;
}

void alekseev::Rectangle::scale(double k)
{
  rect_.width_ *= k;
  rect_.height_ *= k;
}

alekseev::Circle::Circle(double radius, point_t center):
  radius_(radius),
  center_(center)
{
}

double alekseev::Circle::getArea() const
{
  return PI * radius_ * radius_;
}

alekseev::rectangle_t alekseev::Circle::getFrameRect() const
{
  return rectangle_t{2 * radius_, 2 * radius_, center_};
}

void alekseev::Circle::move(point_t new_center)
{
  center_ = new_center;
}

void alekseev::Circle::move(double x, double y)
{
  center_.x_ += x;
  center_.y_ += y;
}

void alekseev::Circle::scale(double k)
{
  radius_ *= k;
}

alekseev::Polygon::Polygon(point_t * points, size_t count)
{
  points_ = new point_t[count];
  count_ = count;
  double area = 0;
  double sumCx = 0;
  double sumCy = 0;
  for (size_t i = 0; i < count; ++i) {
    points_[i] = points[i];
    size_t j = i < count - 1 ? i + 1 : 0;
    double k = points[i].x_ * points[j].y_ - points[i].y_ * points[j].x_;
    area += k;
    sumCx += (points[i].x_ + points[j].x_) * k;
    sumCy += (points[i].y_ + points[j].y_) * k;
  }

  if (!area) {
    sumCx = 0;
    sumCy = 0;
    for (size_t i = 0; i < count; ++i) {
      sumCx += points[i].x_;
      sumCy += points[i].y_;
    }
    sumCx /= count;
    sumCy /= count;
    center_ = point_t{sumCx, sumCy};
  } else {
    area /= 2.0;
    center_ = point_t{sumCx / (6.0 * area), sumCy / (6.0 * area)};
  }
}

alekseev::Polygon::~Polygon()
{
  delete[] points_;
}

double alekseev::Polygon::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < count_; ++i) {
    size_t j = i < count_ - 1 ? i : 0;
    area += points_[i].x_ * points_[j].y_ - points_[i].y_ * points_[j].x_;
  }
  return area / 2.0;
}

alekseev::rectangle_t alekseev::Polygon::getFrameRect() const
{
  double ax = points_[0].x_, ay = points_[0].y_;
  double bx = points_[0].x_, by = points_[0].y_;
  for (size_t i = 1; i < count_; ++i) {
    if (points_[i].x_ < ax) {
      ax = points_[i].x_;
    }
    if (points_[i].y_ < ay) {
      ay = points_[i].y_;
    }
    if (points_[i].x_ > bx) {
      bx = points_[i].x_;
    }
    if (points_[i].y_ > by) {
      by = points_[i].y_;
    }
  }
  point_t p = point_t{(ax + bx) / 2, (ay + by) / 2};
  return rectangle_t{bx - ax, by - ay, p};
}

void alekseev::Polygon::move(point_t new_center)
{
  double dx = new_center.x_ - center_.x_;
  double dy = new_center.y_ - center_.y_;
  move(dx, dy);
}

void alekseev::Polygon::move(double x, double y)
{
  for (size_t i = 0; i < count_; ++i) {
    points_[i].x_ += x;
    points_[i].y_ += y;
  }
  center_.x_ += x;
  center_.y_ += y;
}

void alekseev::Polygon::scale(double k)
{
  if (k == 1) {
    return;
  }
  double xc = center_.x_;
  double yc = center_.y_;
  for (size_t i = 0; i < count_; ++i) {
    points_[i].x_ = k * points_[i].x_ - (k - 1) * xc;
    points_[i].y_ = k * points_[i].y_ - (k - 1) * yc;
  }
}
