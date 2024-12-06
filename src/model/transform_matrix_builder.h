#pragma once

#include "s21_matrix/s21_matrix_oop.h"

namespace s21 {

class TransformMatrixBuilder {
private:
  TransformMatrixBuilder() {};
  ~TransformMatrixBuilder() = default;

public:
  static S21Matrix createRotationMatrix(float a, float b, float c);
  static S21Matrix createMoveMatrix(float a, float b, float c);
  static S21Matrix createScaleMatrix(float a, float b, float c);
};

} // namespace s21
