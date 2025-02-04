#include "transform_matrix.h"

#include "vertex_edge.h"

using namespace s21;

TransformMatrix::TransformMatrix(const TransformMatrix &m)
    : _matrix(m._matrix) {}

TransformMatrix TransformMatrix::operator*(const TransformMatrix &m) {
  this->_matrix = this->_matrix * m._matrix;
  return *this;
}

TransformMatrix &TransformMatrix::operator=(const TransformMatrix &m) {
  this->_matrix = m._matrix;
  return *this;
}

void TransformMatrix::transformPoint(Vertex &v) const {
  float x = v.x() * this->_matrix(0, 0) + v.y() * this->_matrix(1, 0) +
            v.z() * this->_matrix(2, 0) + this->_matrix(3, 0);
  float y = v.x() * this->_matrix(0, 1) + v.y() * this->_matrix(1, 1) +
            v.z() * this->_matrix(2, 1) + this->_matrix(3, 1);
  float z = v.x() * this->_matrix(0, 2) + v.y() * this->_matrix(1, 2) +
            v.z() * this->_matrix(2, 2) + this->_matrix(3, 2);
  v.setX(x);
  v.setY(y);
  v.setZ(z);
}

double &TransformMatrix::operator()(int row, int col) const {
  return _matrix(row, col);
}

void TransformMatrix::InverseTransformMatrix() {
  _matrix = _matrix.InverseMatrix();
}
