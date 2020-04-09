#include "point.h"

void Point::move(double dx, double dy){
  x = x + dx;
  y = y + dy;
}

double Point:: distanceFrom(const Point & p){
  double ans;
  ans = sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
  return ans;
}
