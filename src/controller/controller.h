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
  QString filename = ""; // не занулять при сбросе
};

class Facade {
private:
  Figure model;
  Figure copy_model;
  Parameters p;

  float degreesInRadians(float x);

public:
  Facade() { p = {}; }
  ~Facade() = default;

  void moveFigure(float x, float y, float z);
  void rotateFigure(float x, float y, float z);
  void scaleFigure(float x, float y, float z);
  void resetMovement();
  void loadFile(const QString &filename);

  Figure *getFigure();
  size_t getSizeVertices();
  size_t getSizeFacets();

  // Parameters getParam();
};

} // namespace s21
