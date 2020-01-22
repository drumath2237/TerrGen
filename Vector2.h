#pragma once

#include <iostream>

namespace TerrGen {
  struct Vector2 {
    double x,y;

    Vector2(double x_, double y_):x(x_),y(y_){}
    Vector2():x(0.0),y(0.0){}

    double length() const {
      return sqrt(x*x+y*y);
    }
    double length2() const {
      return x*x+y*y;
    }

    Vector2 operator +(const Vector2& v) const {
      return Vector2(x+v.x, y+v.y);
    }
    Vector2 operator -(const Vector2& v) const {
      return Vector2(x-v.x, y-v.y);
    }
    Vector2 operator *(const Vector2& v) const {
      return Vector2(x*v.x, y*v.y);
    }
    Vector2 operator *(double d) const {
      return Vector2(x*d, y*d);
    }
    Vector2 operator /(const Vector2& v) const {
      if(v.x!=0 && v.y!=0)
        exit(1);

      return Vector2(x/v.x, y/v.y);
    }
    Vector2 operator /(double d) const {
      if(d==0)
        return Vector2(0,0);

      return Vector2(x/d, y/d);
    }

    void normalize() {
      x /= length();
      y /= length();
    }
  };

  Vector2 operator *(double d, const Vector2& v) {
    return Vector2(d*v.x, d*v.y);
  }

  Vector2 normalized(const Vector2& v) {
    return (Vector2)v/v.length();
  }

  double dot(const Vector2& v1, const Vector2& v2) {
    return v1.x*v2.x + v1.y*v2.y;
  }
};