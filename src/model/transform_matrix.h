#pragma once

#include "s21_matrix/s21_matrix_oop.h"

namespace s21 {

class Vertex;

class TransformMatrix {
public:
  S21Matrix _matrix;

public:
  TransformMatrix() : _matrix(S21Matrix(4, 4)) {}
  TransformMatrix(const TransformMatrix &m);
  TransformMatrix(TransformMatrix &&m) noexcept;  // Перемещающий конструктор
  ~TransformMatrix() = default;

  TransformMatrix& operator=(const TransformMatrix &m);  // Оператор копирования
  TransformMatrix& operator=(TransformMatrix &&m) noexcept;  // Оператор перемещения
  TransformMatrix operator*(const TransformMatrix &m);  // Оператор умножения
  double &operator()(int row, int col) const;
  Vertex transformPoint(Vertex &v) const;
  void InverseTransformMatrix();
  void SetIdentityMatrix();


  // Новый метод для проверки корректности
  bool isValid() const;
};

} // namespace s21
