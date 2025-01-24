#include "transform_matrix.h"
#include "vertex_edge.h"

using namespace s21;

TransformMatrix::TransformMatrix(const TransformMatrix &m)
    : _matrix(m._matrix) {}

TransformMatrix TransformMatrix::operator*(const TransformMatrix &m) {
  this->_matrix = this->_matrix * m._matrix;
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

// // Конструктор перемещения
// TransformMatrix::TransformMatrix(TransformMatrix &&m) noexcept
//     : _matrix(std::move(m._matrix)) {}

// // Оператор копирования
// TransformMatrix &TransformMatrix::operator=(const TransformMatrix &m) {
//   if (this != &m) {
//     _matrix = m._matrix;
//   }
//   return *this;
// }

// // Оператор перемещения
// TransformMatrix &TransformMatrix::operator=(TransformMatrix &&m) noexcept {
//   if (this != &m) {
//     _matrix = std::move(m._matrix);
//   }
//   return *this;
// }

double &TransformMatrix::operator()(int row, int col) const {
  return _matrix(row, col);
}

void TransformMatrix::InverseTransformMatrix() {
  _matrix = _matrix.InverseMatrix();
}

// bool TransformMatrix::isValid() const {
//   // Проверяем, что матрица имеет размер 4x4
//   if (_matrix.AccessorRow() != 4 || _matrix.AccessorCol() != 4) {
//     return false;
//   }

//   // Дополнительные проверки, если требуется (например, отсутствие NaN)
//   for (int i = 0; i < 4; ++i) {
//     for (int j = 0; j < 4; ++j) {
//       if (std::isnan(_matrix(i, j)) || std::isinf(_matrix(i, j))) {
//         return false;
//       }
//     }
//   }

//   return true;
// }

// void TransformMatrix::SetIdentityMatrix() {
//     for (int i = 0; i < 4; ++i) {
//         for (int j = 0; j < 4; ++j) {
//             if (i == j) {
//                 (*this)(i, j) = 1.0;
//             } else {
//                 (*this)(i, j) = 0.0;
//             }
//         }
//     }
// }
