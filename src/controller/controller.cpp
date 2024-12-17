#include "controller.h"

#define STEP 5

#include <cmath>

using namespace s21;

float Facade::degreesInRadians(float x) { return x * M_PI / 180; }

void Facade::moveFigure(float x, float y, float z) {
  x /= STEP;
  y /= STEP;
  z /= STEP;
  x -= model.getVertices().begin()->x();
  y -= model.getVertices().begin()->y();
  z -= model.getVertices().begin()->z();
  model.transform(TransformMatrixBuilder::createMoveMatrix(x, y, z));
}
void Facade::rotateFigure(float x, float y, float z) {
  x = degreesInRadians(x);
  y = degreesInRadians(y);
  z = degreesInRadians(z);
  x -= model.getVertices().begin()->x();
  y -= model.getVertices().begin()->y();
  z -= model.getVertices().begin()->z();
  model.transform(TransformMatrixBuilder::createRotationMatrix(x, y, z));
}
void Facade::scaleFigure(float x, float y, float z) {
  // if (x == 0) {
  //   x = 1;
  // } else if (x < 0) {
  //   x = 1 / fabs(x);
  // }
  // if (y == 0) {
  //   y = 1;
  // } else if (y < 0) {
  //   y = 1 / fabs(y);
  // }
  // if (z == 0) {
  //   z = 1;
  // } else if (z < 0) {
  //   z = 1 / fabs(z);
  // }
  model.transform(TransformMatrixBuilder::createScaleMatrix(x, y, z));
}

Figure *Facade::getFigure() { return &model; }