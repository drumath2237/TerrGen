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
  };
};