#include "transform_figure.h"

using namespace s21;

Vertex NormalizeParameters::getMinCoord(QVector<Vertex> &v) {
  Vertex minCoord;

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

Vertex NormalizeParameters::getMaxCoord(QVector<Vertex> &v) {
  Vertex maxCoord;

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

Vertex NormalizeParameters::getCentralCoord(const Vertex minV,
                                            const Vertex maxV) {
  Vertex centr;
  centr.setX(minV.x() + (maxV.x() - minV.x()) / 2);
  centr.setY(minV.y() + (maxV.y() - minV.y()) / 2);
  centr.setZ(minV.z() + (maxV.z() - minV.z()) / 2);

  return centr;
}

void NormalizeParameters::setCentralVertex(QVector<Vertex> &v) {
  Vertex centr = getCentralCoord(getMinCoord(v), getMaxCoord(v));
  for (int i = 0; i < v.size(); i++) {
    v[i] -= centr;
  }
}

void NormalizeParameters::setScaleVertex(QVector<Vertex> &v) {
  Vertex min_coord = getMinCoord(v);
  Vertex scale = getMaxCoord(v) - min_coord;
  if (scale.x() == 0) {
    scale.setX(1);
  }
  if (scale.y() == 0) {
    scale.setY(1);
  }
  if (scale.z() == 0) {
    scale.setZ(1);
  }

  for (int i = 0; i < v.size(); i++) {
    v[i].setX((v[i].x() - min_coord.x()) / scale.x());
    v[i].setY((v[i].y() - min_coord.y()) / scale.y());
    v[i].setZ((v[i].z() - min_coord.z()) / scale.z());
  }
}

void NormalizeParameters::setNormalVertex(QVector<Vertex> &v) {
  setCentralVertex(v);
  setScaleVertex(v);
}
