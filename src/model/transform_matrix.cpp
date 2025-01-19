#include "transform_matrix.h"
#include "vertex_edge.h"

using namespace s21;

// Конструктор копирования
TransformMatrix::TransformMatrix(const TransformMatrix &m) 
    : _matrix(m._matrix) {}

// Конструктор перемещения
TransformMatrix::TransformMatrix(TransformMatrix &&m) noexcept 
    : _matrix(std::move(m._matrix)) {}

// Оператор копирования
TransformMatrix& TransformMatrix::operator=(const TransformMatrix &m) {
  if (this != &m) {
    _matrix = m._matrix;
  }
  return *this;
}

// Оператор перемещения
TransformMatrix& TransformMatrix::operator=(TransformMatrix &&m) noexcept {
  if (this != &m) {
    _matrix = std::move(m._matrix);
  }
  return *this;
}

TransformMatrix TransformMatrix::operator*(const TransformMatrix &m) {
  // Вместо копирования объекта, используем его по ссылке
  TransformMatrix result(*this);  // Копируем *this
  result._matrix = this->_matrix * m._matrix;
  return result;  // Возвращаем результат по значению
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

void TransformMatrix::InverseTransformMatrix() {
  _matrix = _matrix.InverseMatrix();
}

bool TransformMatrix::isValid() const {
  // Проверяем, что матрица имеет размер 4x4
  if (_matrix.AccessorRow() != 4 || _matrix.AccessorCol() != 4) {
    return false;
  }

  // Дополнительные проверки, если требуется (например, отсутствие NaN)
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (std::isnan(_matrix(i, j)) || std::isinf(_matrix(i, j))) {
        return false;
      }
    }
  }

  return true;
}


void TransformMatrix::SetIdentityMatrix() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == j) {
                (*this)(i, j) = 1.0;
            } else {
                (*this)(i, j) = 0.0;
            }
        }
    }
}
