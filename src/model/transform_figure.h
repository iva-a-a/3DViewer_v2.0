#pragma once
#include "parser.h"

namespace s21 {

class NormalizeParameters {
private:
  QVector<QVector3D> v;
  QVector<QVector<int>> f;

public:
  // NormalizeParameters();
  //~NormalizeParameters();

  QVector3D getCentralCoord(const QVector3D minV, const QVector3D maxV);

  QVector3D getMinCoord(const QVector<QVector3D> v);
  QVector3D getMaxCoord(const QVector<QVector3D> v);

  void setNormalVertex(const QVector<QVector3D> vertex);
  void setNormalEdge(QVector<QVector<int>> edge);
};

} // namespace s21