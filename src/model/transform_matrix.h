#pragma once

#include "s21_matrix/s21_matrix_oop.h"

namespace s21 {

class Vertex;

/**
 * @class TransformMatrix
 * @brief Класс для матрицы преобразования.
 */
class TransformMatrix {
 private:
  /** Матрица преобразования. */
  S21Matrix _matrix;

 public:
  /**
   * @brief Конструктор класса TransformMatrix по умолчанию.
   */
  TransformMatrix() : _matrix(S21Matrix(4, 4)) {}

  /**
   * @brief Конструктор копирования.
   */
  TransformMatrix(const TransformMatrix& m) : _matrix(m._matrix) {}

  /**
   * @brief Конструктор перемещения.
   */
  TransformMatrix(TransformMatrix&& m) noexcept : _matrix(std::move(m._matrix)) {}

  /**
   * @brief Оператор присваивания (копирование).
   */
  TransformMatrix& operator=(const TransformMatrix& m) {
    if (this != &m) {
      _matrix = m._matrix;
    }
    return *this;
  }

  /**
   * @brief Оператор присваивания (перемещение).
   */
  TransformMatrix& operator=(TransformMatrix&& m) noexcept {
    if (this != &m) {
      _matrix = std::move(m._matrix);
    }
    return *this;
  }

  /**
   * @brief Деструктор.
   */
  ~TransformMatrix() = default;

  /**
   * @brief Оператор умножения матриц трансформирования.
   * @param m Ссылка на матрицу для умножения.
   * @return Результат умножения матриц.
   */
  TransformMatrix operator*(const TransformMatrix& m);

  /**
   * @brief Оператор доступа к элементу матрицы.
   * @param row Индекс строки.
   * @param col Индекс столбца.
   * @return Ссылка на элемент матрицы.
   */
  double& operator()(int row, int col) const;

  /**
   * @brief Применение преобразования к вершине.
   * @param v Ссылка на вершину.
   */
  void transformPoint(Vertex& v) const;

  /**
   * @brief Нахождение обратной матрицы.
   */
  void InverseTransformMatrix();
};

}  // namespace s21
