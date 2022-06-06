#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector2d.h"

class Transform {
  public:
    float X, Y;
  public:
    Transform(float x = 0, float y = 0) : X(x), Y(y) {}
    void Log(std::string mess = "") {
      std::cout << mess << "(x, y) : (" << X << ", " << Y << ")" << std::endl;
    }

  public:
    inline TranslateX(float x) {X += x;}
    inline TranslateY(float y) {Y += y;}
    inline Translate(vector2d v) {
      X += v.X;
      Y += v.Y;
    }

};

#endif // TRANSFORM_H
