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
  Figure copy_model;
  Parameters p;

  float degreesInRadians(float x);

public:
  Facade(const QString &filename) : model(Figure(filename)), copy_model(model) {
    p = {};
  }
  ~Facade() = default;

  void moveFigure(float x, float y, float z);
  void rotateFigure(float x, float y, float z);
  void scaleFigure(float x, float y, float z);
  void resetMovement();

  Figure *getFigure();

  // Parameters getParam();

  // void setRotateX(float x) { p.rotate_x = x; }
  // void setRotateY(float y) { p.rotate_y = y; }
  // void setRotateZ(float z) { p.rotate_z = z; }
};

} // namespace s21
