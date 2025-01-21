#pragma once

#include <QVector>

#include "vertex_edge.h"

namespace s21 {

class NormalizeParameters {
 private:
  static Vertex getMinCoord(const QVector<Vertex> &v);
  static Vertex getMaxCoord(const QVector<Vertex> &v);
  static Vertex getCentralCoord(const Vertex minV, const Vertex maxV);

  static void setCentralVertex(QVector<Vertex> &v);
  static void setScaleVertex(QVector<Vertex> &v);

  NormalizeParameters() {};
  ~NormalizeParameters() = default;

 public:
  static void setNormalVertex(QVector<Vertex> &v);
  static void remDuplicateFaces(QVector<Edge> &f);
};

}  // namespace s21