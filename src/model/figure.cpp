#include "figure.h"

#include <unordered_map>

using namespace s21;

Figure::Figure(const QString &filename) {
  Parser::recordCoordFromFile(filename, vertices, facets);
  if (!vertices.isEmpty()) {
    NormalizeParameters::setNormalVertex(vertices);
  }
}

Figure::Figure(Figure &f) {
  std::unordered_map<uint64_t, int> v_map;
  vertices.clear();
  vertices.reserve(f.vertices.size());
  for (int i = 0; i < f.vertices.size(); i++) {
    vertices.push_back(f.vertices[i]);
    v_map.insert({uint64_t(&f.vertices[i]), i});
  }
  facets.clear();
  facets.reserve(f.facets.size());
  for (int i = 0; i < f.facets.size(); i++) {
    const Vertex &begin = f.facets[i].getBeginPosition();
    const Vertex &end = f.facets[i].getEndPosition();
    int index_begin = v_map[uint64_t(&begin)];
    int index_end = v_map[uint64_t(&end)];
    facets.push_back(Edge(vertices[index_begin], vertices[index_end]));
  }
}

Figure &Figure::operator=(Figure &f) {
  std::unordered_map<uint64_t, int> v_map;
  vertices.clear();
  vertices.reserve(f.vertices.size());
  for (int i = 0; i < f.vertices.size(); i++) {
    vertices.push_back(f.vertices[i]);
    v_map.insert({uint64_t(&f.vertices[i]), i});
  }
  facets.clear();
  facets.reserve(f.facets.size());
  for (int i = 0; i < f.facets.size(); i++) {
    const Vertex &begin = f.facets[i].getBeginPosition();
    const Vertex &end = f.facets[i].getEndPosition();
    int index_begin = v_map[uint64_t(&begin)];
    int index_end = v_map[uint64_t(&end)];
    facets.push_back(Edge(vertices[index_begin], vertices[index_end]));
  }
  return *this;
}

void Figure::transform(const TransformMatrix &m) {
  for (auto &i : vertices) {
    i.transform(m);
  }
}

const QVector<Vertex> Figure::getVertices() { return vertices; }

const QVector<Edge> Figure::getFacets() { return facets; }