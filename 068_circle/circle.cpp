#include "circle.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  //double ans=0;
  double PI = 2 * asin(1.0);
  double dis = center.distanceFrom(otherCircle.center);
  if (dis >= radius + otherCircle.radius || !radius || !otherCircle.radius) {
    return 0;
  }
  else if (dis <= fabs(radius - otherCircle.radius)) {
    if (radius > otherCircle.radius) {
      return otherCircle.radius * otherCircle.radius * PI;
    }
    else {
      return radius * radius * PI;
    }
  }
  else {
    float halfOfA =
        acos((pow(dis, 2) + pow(radius, 2) - pow(otherCircle.radius, 2)) / (2 * dis * radius));
    float halfOfB = acos((pow(dis, 2) - pow(radius, 2) + pow(otherCircle.radius, 2)) /
                         (2 * dis * otherCircle.radius));
    float AreaofSectorA = halfOfA * radius * radius;
    float AreaofSectorB = halfOfB * pow(otherCircle.radius, 2);
    float AreaofTriA = radius * radius * sin(halfOfA) * cos(halfOfA);
    float AreaofTriB = pow(otherCircle.radius, 2) * sin(halfOfB) * cos(halfOfB);
    return AreaofSectorA + AreaofSectorB - AreaofTriA - AreaofTriB;
  }
}
