#pragma once
// #include "parser.h"
#include <QVector3D>
#include <QVector>

namespace s21 {

class NormalizeParameters {
private:
  static QVector3D getMinCoord(QVector<QVector3D> &v);
  static QVector3D getMaxCoord(QVector<QVector3D> &v);
  static QVector3D getCentralCoord(const QVector3D minV, const QVector3D maxV);

  static void setCentralVertex(QVector<QVector3D> &vertex);
  static void setScaleVertex(QVector<QVector3D> &vertex);

public:
  NormalizeParameters() {};
  ~NormalizeParameters() = default;

  static void setNormalVertex(QVector<QVector3D> &vertex);

  // void setNormalEdge(QVector<QVector<int>> edge);
};

} // namespace s21