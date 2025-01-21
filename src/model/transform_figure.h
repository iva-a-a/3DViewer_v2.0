#pragma once

#include "vertex_edge.h"
#include <QVector>

namespace s21 {

class NormalizeParameters {
public:
  static Vertex getMinCoord(QVector<Vertex> &v);
  static Vertex getMaxCoord(QVector<Vertex> &v);
  static Vertex getCentralCoord(const Vertex minV, const Vertex maxV);

  static void setCentralVertex(QVector<Vertex> &v);
  static void setScaleVertex(QVector<Vertex> &v);

  NormalizeParameters() {};
  ~NormalizeParameters() = default;

public:
  static void setNormalVertex(QVector<Vertex> &v);
};

} // namespace s21