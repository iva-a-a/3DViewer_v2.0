#pragma once

#include "parser.h"
#include "transform_matrix_builder.h"

/**
 * @class Figure
 * @brief Класс представляет фигуру, состоящую из вершин и граней.
 */
class Figure {
 private:
  /** Список вершин фигуры. */
  QVector<Vertex> vertices = {};
  /** Список граней фигуры. */
  QVector<Edge> facets = {};

 public:
  /**
   * @brief Конструктор класса Figure по умолчанию.
   */
  Figure() {}
  /**
   * @brief Конструктор класса Figure.
   * @param filename Имя файла с данными.
   */
  explicit Figure(const QString &filename);
  /**
   * @brief Конструктор копирования класса Figure.
   * @param f Ссылка на объект Figure для копирования.
   */
  Figure(const Figure &f);
  /**
   * @brief Деструктор класса Figure.
   */
  ~Figure() = default;

  /**
   * @brief Оператор присваивания для класса Figure.
   * @param f Ссылка на объект Figure для присваивания.
   * @return Ссылка на текущий объект Figure.
   */
  Figure &operator=(const Figure &f);

  /**
   * @brief Применение преобразований к вершинам фигуры.
   * @param m Матрица преобразования.
   */
  void transform(const TransformMatrix &m);

  /**
   * @brief Получение списка вершин фигуры.
   * @return Список вершин.
   */
  const QVector<Vertex> getVertices();

  /**
   * @brief Получение списка граней фигуры.
   * @return Список граней.
   */
  const QVector<Edge> getFacets();
};
