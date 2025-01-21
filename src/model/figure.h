#pragma once

#include "parser.h"
#include "transform_matrix_builder.h"

namespace s21 {

class Figure {
 private:
  QVector<Vertex> vertices = {};
  QVector<Edge> facets = {};

 public:
  Figure() {};
  Figure(const QString &filename);
  Figure(const Figure &f);
  ~Figure() = default;

  Figure &operator=(const Figure &f);

  void transform(const TransformMatrix &m);

  const QVector<Vertex> getVertices();
  const QVector<Edge> getFacets();
};

}  // namespace s21
