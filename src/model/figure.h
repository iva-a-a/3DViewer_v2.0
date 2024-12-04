#pragma once
#include "parser.h"

namespace s21 {

class Figure {
private:
  QVector<QVector3D> vertices;  // координаты вершин
  QVector<QVector<int>> facets; // индексы вершин, составляющих грани
public:
  Figure(const QString &filename);
  ~Figure() = default;
  const QVector<QVector3D> getVertices();
  const QVector<QVector<int>> getFacets();
};

} // namespace s21
