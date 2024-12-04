#include "figure.h"

using namespace s21;

Figure::Figure(const QString &filename) {
  Parser::recordCoordFromFile(filename, this->vertices, this->facets);
  if (!vertices.isEmpty()) {
    NormalizeParameters::setNormalVertex(this->vertices);
  }
}

const QVector<QVector3D> Figure::getVertices() { return vertices; }

const QVector<QVector<int>> Figure::getFacets() { return facets; }