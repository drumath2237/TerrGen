#include <iostream>

namespace TerrGen {
  struct Vector2 {
    double x,y;

    Vector2(double x_, double y_):x(x_),y(y_){}
    Vector2():x(0.0),y(0.0){}

    double length() {
      return sqrt(x*x+y*y);
    }
    double length2() {
      return x*x+y*y;
    }

    Vector2 operator +(const Vector2& v) {
      return Vector2(x+v.x, y+v.y);
    }
    Vector2 operator -(const Vector2& v) {
      return Vector2(x-v.x, y-v.y);
    }
    Vector2 operator *(const Vector2& v) {
      return Vector2(x*v.x, y*v.y);
    }
    Vector2 operator *(double d) {
      return Vector2(x*d, y*d);
    }
    Vector2 operator /(const Vector2& v) {
      if(v.x!=0 && v.y!=0)
        exit(1);

      return Vector2(x/v.x, y/v.y);
    }
    Vector2 operator /(double d) {
      if(d!=0)
        exit(1);

      return Vector2(x/d, y/d);
    }
  };

  Vector2 operator *(double d, const Vector2& v) {
    return Vector2(d*v.x, d*v.y);
  }
};