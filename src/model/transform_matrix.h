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
   * @brief Конструктор копирования класса TransformMatrix.
   * @param m Ссылка на объект TransformMatrix для копирования.
   */
  TransformMatrix(const TransformMatrix &m);

  /**
   * @brief Деструктор класса TransformMatrix.
   */
  ~TransformMatrix() = default;

  /**
   * @brief Оператор умножения матриц трансформирования.
   * @param m Ссылка на матрицу для умножения.
   * @return Результат умножения матриц.
   */
  TransformMatrix operator*(const TransformMatrix &m);

  /**
   * @brief Оператор присваивания (копирования) матриц трансформирования.
   * @param m Ссылка на матрицу для копирования.
   * @return Ссылка на текущий объект матрицы трансформирования после
   * присваивания.
   */
  TransformMatrix &operator=(const TransformMatrix &m);

  /**
   * @brief Оператор доступа к элементу матрицы.
   * @param row Индекс строки.
   * @param col Индекс столбца.
   * @return Ссылка на элемент матрицы.
   */
  double &operator()(int row, int col) const;

  /**
   * @brief Применение преобразования к вершине.
   * @param v Ссылка на вершину.
   */
  void transformPoint(Vertex &v) const;

  /**
   * @brief Нахождение обратной матрицы.
   */
  void InverseTransformMatrix();
};

}  // namespace s21
