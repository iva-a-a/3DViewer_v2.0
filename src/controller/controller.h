#pragma once

#include "../model/figure.h"

namespace s21 {
struct Parameters {
  float scale = 1.0f;
  float shift_x = 0.0f;
  float shift_y = 0.0f;
  float shift_z = 0.0f;
  float rotate_x = 0.0f;
  float rotate_y = 0.0f;
  float rotate_z = 0.0f;
};

class Facade {
private:
  Figure model;
  Parameters p;
  float degreesInRadians(float x);

public:
  Facade(const QString &filename) : model(Figure(filename)) { p = {}; }
  ~Facade() = default;

  void moveFigure(float x, float y, float z);
  void rotateFigure(float x, float y, float z);
  void scaleFigure(float x, float y, float z);

  Figure *getFigure();
};

} // namespace s21
