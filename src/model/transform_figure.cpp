#include "transform_figure.h"

#include <unordered_set>

using namespace s21;

Vertex NormalizeParameters::getMinCoord(const QVector<Vertex> &v) {
  Vertex minCoord;

  minCoord = v[0];
  for (const auto &i : v) {
    minCoord.setX(std::min(i.x(), minCoord.x()));
    minCoord.setY(std::min(i.y(), minCoord.y()));
    minCoord.setZ(std::min(i.z(), minCoord.z()));
  }
  return minCoord;
}

Vertex NormalizeParameters::getMaxCoord(const QVector<Vertex> &v) {
  Vertex maxCoord;

  maxCoord = v[0];
  for (const auto &i : v) {
    maxCoord.setX(std::max(i.x(), maxCoord.x()));
    maxCoord.setY(std::max(i.y(), maxCoord.y()));
    maxCoord.setZ(std::max(i.z(), maxCoord.z()));
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
  Vertex max_coord = getMaxCoord(v);
  Vertex scale = max_coord - min_coord;

  float common_scale = std::max({scale.x(), scale.y(), scale.z()});
  common_scale = common_scale == 0.0f ? 1.0f : common_scale;

  bool is_already_normalized = true;
  for (const auto &vertex : v) {
    if (vertex.x() < -1 || vertex.x() > 1 ||
        vertex.y() < -1 || vertex.y() > 1 ||
        vertex.z() < -1 || vertex.z() > 1) {
      is_already_normalized = false;
      break;
    }
  }

  if (is_already_normalized) {
    return;
  }

  Vertex center = getCentralCoord(min_coord, max_coord);

  for (int i = 0; i < v.size(); ++i) {
    v[i].setX((v[i].x() - center.x()) / common_scale * 2);
    v[i].setY((v[i].y() - center.y()) / common_scale * 2);
    v[i].setZ((v[i].z() - center.z()) / common_scale * 2);
  }
}

void NormalizeParameters::setNormalVertex(QVector<Vertex> &v) {
  setCentralVertex(v);
  setScaleVertex(v);
}

void NormalizeParameters::remDuplicateFaces(QVector<Edge> &f) {
  std::unordered_set<Edge, Edge::HashEdge> unique_facets;
  QVector<Edge> tmp;
  for (const auto &i : f) {
    if (unique_facets.insert(i).second) {
      tmp.append(i);
    }
  }
  f = tmp;
}
