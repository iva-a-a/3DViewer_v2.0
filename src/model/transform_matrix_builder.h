#pragma once

#include "transform_matrix.h"

namespace s21 {

class TransformMatrixBuilder {
private:
  TransformMatrixBuilder() {};
  ~TransformMatrixBuilder() = default;

public:
  static TransformMatrix createRotateMatrix(float a, float b, float c);
  static TransformMatrix createMoveMatrix(float a, float b, float c);
  static TransformMatrix createScaleMatrix(float a, float b, float c);
  static TransformMatrix createPerspectiveMatrix(float fov, float aspect,
                                                 float near, float far);
};

} // namespace s21
