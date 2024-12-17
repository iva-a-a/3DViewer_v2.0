#pragma once

#include "../model/figure.h"

namespace s21 {

class Facade {
private:
  Figure model;

  float degreesInRadians(float x);

public:
  Facade(const QString &filename) : model(Figure(filename)) {}
  ~Facade() = default;

  void moveFigure(float x, float y, float z);
  void rotateFigure(float x, float y, float z);
  void scaleFigure(float x, float y, float z);

  Figure *getFigure();
};

} // namespace s21