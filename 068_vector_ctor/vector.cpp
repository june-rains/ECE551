#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

double Vector2D::getMagnitude() const {
  using std::sqrt;
  return sqrt(dot(*this));
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D newVector;
  newVector.x = x + rhs.x;
  newVector.y = y + rhs.y;
  return newVector;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  double result;
  result = x * rhs.x + y * rhs.y;
  return result;
}

void Vector2D::print() const {
  std::printf("<%.2f, %.2f>", x, y);
}
