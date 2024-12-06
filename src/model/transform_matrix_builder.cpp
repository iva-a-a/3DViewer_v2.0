#include "transform_matrix_builder.h"

#include <cmath>
using namespace s21;

S21Matrix TransformMatrixBuilder::createRotationMatrix(float a, float b,
                                                       float c) {

  S21Matrix matrix(4, 4);

  matrix(0, 0) = cos(b) * cos(c);
  matrix(0, 1) = -sin(c) * cos(b);
  matrix(0, 2) = sin(b);
  matrix(0, 3) = 0;
  matrix(1, 0) = sin(a) * sin(b) * cos(c) + sin(c) * cos(a);
  matrix(1, 1) = -sin(a) * sin(b) * sin(c) + cos(a) * cos(c);
  matrix(1, 2) = -sin(a) * cos(b);
  matrix(1, 3) = 0;
  matrix(2, 0) = sin(a) * sin(c) - sin(b) * cos(a) * cos(c);
  matrix(2, 1) = sin(a) * cos(c) + sin(b) * sin(c) * cos(a);
  matrix(2, 2) = cos(a) * cos(b);
  matrix(2, 3) = 0;
  matrix(3, 0) = 0;
  matrix(3, 1) = 0;
  matrix(3, 2) = 0;
  matrix(3, 3) = 1;

  return matrix;
}

S21Matrix TransformMatrixBuilder::createMoveMatrix(float a, float b, float c) {
  S21Matrix matrix(4, 4);

  matrix(0, 0) = 1;
  matrix(0, 1) = 0;
  matrix(0, 2) = 0;
  matrix(0, 3) = a;
  matrix(1, 0) = 0;
  matrix(1, 1) = 1;
  matrix(1, 2) = 0;
  matrix(1, 3) = b;
  matrix(2, 0) = 0;
  matrix(2, 1) = 0;
  matrix(2, 2) = 1;
  matrix(2, 3) = c;
  matrix(3, 0) = 0;
  matrix(3, 1) = 0;
  matrix(3, 2) = 0;
  matrix(3, 3) = 1;

  return matrix;
}

S21Matrix TransformMatrixBuilder::createScaleMatrix(float a, float b, float c) {
  S21Matrix matrix(4, 4);

  matrix(0, 0) = a;
  matrix(0, 1) = 0;
  matrix(0, 2) = 0;
  matrix(0, 3) = 0;
  matrix(1, 0) = 0;
  matrix(1, 1) = b;
  matrix(1, 2) = 0;
  matrix(1, 3) = 0;
  matrix(2, 0) = 0;
  matrix(2, 1) = 0;
  matrix(2, 2) = c;
  matrix(2, 3) = 0;
  matrix(3, 0) = 0;
  matrix(3, 1) = 0;
  matrix(3, 2) = 0;
  matrix(3, 3) = 1;

  return matrix;
}