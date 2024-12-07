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
  S21Matrix mat_point(4, 1);
  S21Matrix m(this->_matrix);
  Vertex result;
  mat_point(0, 0) = v.x();
  mat_point(1, 0) = v.y();
  mat_point(2, 0) = v.z();
  mat_point(3, 0) = 1;

  m.MulMatrix(mat_point);

  result.setX(m(0, 0));
  result.setY(m(1, 0));
  result.setZ(m(2, 0));

  return result;
}

double &TransformMatrix::operator()(int row, int col) const {
  return _matrix(row, col);
}
