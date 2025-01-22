#pragma once
#include <QVector3D>

#include "transform_matrix.h"

namespace s21 {

/**
 * @class Vertex
 * @brief Класс представления вершины.
 */
class Vertex : public QVector3D {
 public:
  /**
   * @brief Конструктор класса Vertex по умолчанию.
   */
  Vertex() : QVector3D() {}

  /**
   * @brief Конструктор класса Vertex.
   * @param x Координата X.
   * @param y Координата Y.
   * @param z Координата Z.
   */
  Vertex(float x, float y, float z) : QVector3D(x, y, z) {}

  /**
   * @brief Конструктор копирования класса Vertex.
   * @param v Ссылка на объект QVector3D для копирования.
   */
  Vertex(const QVector3D &v) : QVector3D(v) {}

  /**
   * @brief Деструктор класса Vertex.
   */
  ~Vertex() = default;

  /**
   * @brief Применение преобразования к вершине.
   * @param m Ссылка на матрицу преобразования.
   */
  void transform(const TransformMatrix &m) { *this = m.transformPoint(*this); }
};

/**
 * @class Edge
 * @brief Класс представления ребра.
 */
class Edge {
 private:
  /** Указатель на начальную вершину. */
  Vertex *_begin;
  /** Указатель на конечную вершину. */
  Vertex *_end;

 public:
  /**
   * @brief Конструктор класса Edge.
   * @param begin Указатель на начальную вершину.
   * @param end Указатель на конечную вершину.
   */
  Edge(Vertex *begin, Vertex *end) : _begin(begin), _end(end) {}

  /**
   * @brief Деструктор класса Edge.
   */
  ~Edge() = default;

  /**
   * @brief Получение начальной вершины ребра.
   * @return Указатель на начальную вершину.
   */
  const Vertex *getBeginPosition() const { return _begin; }

  /**
   * @brief Получение конечной вершины ребра.
   * @return Указатель на конечную вершину.
   */
  const Vertex *getEndPosition() const { return _end; }

  /**
   * @brief Оператор сравнения ребер.
   * @param e Ссылка на ребро для сравнения.
   * @return true, если ребра равны, иначе false.
   */
  bool operator==(const Edge &e) const {
    return (_begin == e._begin && _end == e._end) ||
           (_begin == e._end && _end == e._begin);
  }

  /**
   * @brief Структура для хеширования ребра.
   */
  struct HashEdge {
    size_t operator()(const Edge &e) const {
      return std::hash<Vertex *>()(e._begin) ^ std::hash<Vertex *>()(e._end);
    }
  };
};

}  // namespace s21