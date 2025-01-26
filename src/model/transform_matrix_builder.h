#pragma once

#include "transform_matrix.h"

namespace s21 {

/**
 * @class TransformMatrixBuilder
 * @brief Класс для создания матриц движения.
 */
class TransformMatrixBuilder {
 private:
  /**
   * @brief Конструктор класса TransformMatrixBuilder.
   */
  TransformMatrixBuilder() {};

  /**
   * @brief Деструктор класса TransformMatrixBuilder.
   */
  ~TransformMatrixBuilder() = default;

 public:
  /**
   * @brief Создание матрицы поворота.
   * @param a Угол поворота по оси OX.
   * @param b Угол поворота по оси OY.
   * @param c Угол поворота по оси OZ.
   * @return Матрица поворота.
   */
  static TransformMatrix createRotateMatrix(float a, float b, float c);

  /**
   * @brief Создание матрицы перемещения.
   * @param a Смещение по оси OX.
   * @param b Смещение по оси OY.
   * @param c Смещение по оси OZ.
   * @return Матрица перемещения.
   */
  static TransformMatrix createMoveMatrix(float a, float b, float c);

  /**
   * @brief Создание матрицы масштабирования.
   * @param a Масштабирование по оси OX.
   * @param b Масштабирование по оси OY.
   * @param c Масштабирование по оси OZ.
   * @return Матрица масштабирования.
   */
  static TransformMatrix createScaleMatrix(float a, float b, float c);
};

}  // namespace s21
