#include "transform_figure.h"

using namespace s21;

QVector3D NormalizeParameters::getMinCoord(QVector<QVector3D> &v) {
  QVector3D minCoord;

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
  return minCoord;
}

QVector3D NormalizeParameters::getMaxCoord(QVector<QVector3D> &v) {
  QVector3D maxCoord;

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
  return maxCoord;
}

QVector3D NormalizeParameters::getCentralCoord(const QVector3D minV,
                                               const QVector3D maxV) {
  QVector3D centr;
  centr.setX(minV.x() + (maxV.x() - minV.x()) / 2);
  centr.setY(minV.y() + (maxV.y() - minV.y()) / 2);
  centr.setZ(minV.z() + (maxV.z() - minV.z()) / 2);

  return centr;
}

void NormalizeParameters::setCentralVertex(QVector<QVector3D> &vertex) {
  QVector3D centr = getCentralCoord(getMinCoord(vertex), getMaxCoord(vertex));
  for (int i = 0; i < vertex.size(); i++) {
    vertex[i] -= centr;
  }
}

void NormalizeParameters::setScaleVertex(QVector<QVector3D> &vertex) {
  QVector3D min_coord = getMinCoord(vertex);
  QVector3D scale = getMaxCoord(vertex) - min_coord;
  if (scale.x() == 0) {
    scale.setX(1);
  }
  if (scale.y() == 0) {
    scale.setY(1);
  }
  if (scale.z() == 0) {
    scale.setZ(1);
  }

  for (int i = 0; i < vertex.size(); i++) {
    vertex[i].setX((vertex[i].x() - min_coord.x()) / scale.x());
    vertex[i].setY((vertex[i].y() - min_coord.y()) / scale.y());
    vertex[i].setZ((vertex[i].z() - min_coord.z()) / scale.z());
  }
}

void NormalizeParameters::setNormalVertex(QVector<QVector3D> &vertex) {
  setCentralVertex(vertex);
  setScaleVertex(vertex);
}
