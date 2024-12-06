#pragma once
#include "parser.h"

namespace s21 {

class Figure {
private:
  QVector<Vertex> vertices;
  QVector<Edge> facets;

public:
  Figure(const QString &filename);
  ~Figure() = default;

  const QVector<Vertex> getVertices();
  const QVector<Edge> getFacets();
};

} // namespace s21
