#include "point.hpp"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>

void Point::move(double dx, double dy) {
  x = x + dx;
  y = y + dy;
}

double Point::distanceFrom(const Point & p) {
  double disx = p.x - x;
  double disx2 = disx * disx;
  double disy = p.y - y;
  double disy2 = disy * disy;
  return sqrt(disx2 + disy2);
}
