#include "figure.h"

using namespace s21;

Figure::Figure(const QString &filename) {
  Parser::recordCoordFromFile(filename, vertices, facets);
  if (!vertices.isEmpty()) {
    NormalizeParameters::setNormalVertex(vertices);
  }
}

const QVector<Vertex> Figure::getVertices() { return vertices; }

const QVector<Edge> Figure::getFacets() { return facets; }