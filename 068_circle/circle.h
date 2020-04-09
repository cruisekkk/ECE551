#include "point.h"

// class prototype
class Circle
{
 private:
  Point center;
  const double radius;

 public:
  Circle(const Point & c, const double r) : center(c), radius(r) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
