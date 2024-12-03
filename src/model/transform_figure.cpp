#include "transform_figure.h"

using namespace s21;

QVector3D NormalizeParameters::getCentralCoord(const QVector3D minV,
                                               const QVector3D maxV) {
  QVector3D centr;
  if (!minV.isEmpty() && !maxV.isEmpty()) {
    centr.setX(minV.x() + (maxV.x() - minV.x()) / 2);
    centr.setY(minV.y() + (maxV.y() - minV.y()) / 2);
    centr.setZ(minV.z() + (maxV.z() - minV.z()) / 2);
  }
  return centr;
}

QVector3D NormalizeParameters::getMinCoord(const QVector<QVector3D> v) {
  QVector3D minCoord;
  if (!v.isEmpty()) {
    minCoord = v[0];
    for (const auto &i : v) {
      if (i.x() < minCoord.x()) {
        minCoord.setX(i.x());
      }
      if (i.y() < minCoord.y()) {
        minCoord.setY(i.y());
      }
      if (i.z() < minCoord.z()) {
        minCoord.setZ(i.z());
      }
    }
  }
  return minCoord;
}

QVector3D NormalizeParameters::getMaxCoord(const QVector<QVector3D> v) {
  QVector3D maxCoord;
  if (!v.isEmpty()) {
    maxCoord = v[0];
    for (const auto &i : v) {
      if (i.x() > maxCoord.x()) {
        maxCoord.setX(i.x());
      }
      if (i.y() > maxCoord.y()) {
        maxCoord.setY(i.y());
      }
      if (i.z() > maxCoord.z()) {
        maxCoord.setZ(i.z());
      }
    }
  }
  return maxCoord;
}

void NormalizeParameters::setNormalVertex(const QVector<QVector3D> vertex) {
  QVector3D centr = getCentralCoord(getMinCoord(vertex), getMaxCoord(vertex));
  for (int i = 0; i < vertex.size(); i++) {
    v[i] = vertex[i] - centr;
  }
}

void NormalizeParameters::setNormalEdge(QVector<QVector<int>> edge) {
  this->f = edge;
}