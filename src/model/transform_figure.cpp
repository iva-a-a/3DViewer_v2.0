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

Vertex NormalizeParameters::getCentralCoord(const Vertex &minCoord, const Vertex &maxCoord) {
    float centerX = (minCoord.x() + maxCoord.x()) / 2;
    float centerY = (minCoord.y() + maxCoord.y()) / 2;
    float centerZ = (minCoord.z() + maxCoord.z()) / 2;
    return Vertex(centerX, centerY, centerZ);
}

void NormalizeParameters::setCentralVertex(QVector<Vertex> &v) {
    // Получаем минимальные и максимальные координаты
    Vertex minCoord = getMinCoord(v);
    Vertex maxCoord = getMaxCoord(v);

    // Вычисляем центральную точку
    Vertex centr = getCentralCoord(minCoord, maxCoord);
    
    // Сдвигаем вершины так, чтобы центр был в (0, 0, 0)
    for (int i = 0; i < v.size(); i++) {
        v[i].setX(v[i].x() - centr.x());  // Сдвиг по оси X
        v[i].setY(v[i].y() - centr.y());  // Сдвиг по оси Y
        v[i].setZ(v[i].z() - centr.z());  // Сдвиг по оси Z
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
    v[i].setX(((v[i].x() - min_coord.x()) / scale.x()) * 2 - 1);
    v[i].setY(((v[i].y() - min_coord.y()) / scale.y()) * 2 - 1);
    v[i].setZ(((v[i].z() - min_coord.z()) / scale.z()) * 2 - 1);
  }
}

void NormalizeParameters::setNormalVertex(QVector<Vertex> &v) {
  setCentralVertex(v);
  setScaleVertex(v);
}
