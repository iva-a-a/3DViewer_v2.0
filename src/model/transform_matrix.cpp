#include "transform_matrix.h"

#include "vertex_edge.h"

using namespace s21;

TransformMatrix::TransformMatrix(const TransformMatrix &m)
    : _matrix(m._matrix) {}

TransformMatrix TransformMatrix::operator*(const TransformMatrix &m) {
  this->_matrix = this->_matrix * m._matrix;
  return *this;
}

Vertex TransformMatrix::transformPoint(Vertex &v) const {
  S21Matrix mat_point(1, 4);
  S21Matrix m(this->_matrix);
  Vertex result;
  mat_point(0, 0) = v.x();
  mat_point(0, 1) = v.y();
  mat_point(0, 2) = v.z();
  mat_point(0, 3) = 1;

  mat_point.MulMatrix(m);

  result.setX(mat_point(0, 0));
  result.setY(mat_point(0, 1));
  result.setZ(mat_point(0, 2));

  return result;
}

double &TransformMatrix::operator()(int row, int col) const {
  return _matrix(row, col);
}

void TransformMatrix::InverseTransformMatrix() {
  _matrix = _matrix.InverseMatrix();
}