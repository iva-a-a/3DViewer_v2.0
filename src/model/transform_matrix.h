#pragma once

#include "s21_matrix/s21_matrix_oop.h"

namespace s21 {

class Vertex;

class TransformMatrix {
private:
  S21Matrix _matrix;

public:
  TransformMatrix() : _matrix(S21Matrix(4, 4)) {}
  TransformMatrix(const TransformMatrix &m);
  ~TransformMatrix() = default;
  TransformMatrix operator*(const TransformMatrix &m);
  double &operator()(int row, int col) const;
  Vertex transformPoint(Vertex &v) const;
  void InverseTransformMatrix();
};

} // namespace s21