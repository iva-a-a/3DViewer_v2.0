#include "figure.h"

#include <unordered_map>

using namespace s21;

Figure::Figure(const QString &filename) {
  Parser::recordCoordFromFile(filename, vertices, facets);
  if (!vertices.isEmpty()) {
    NormalizeParameters::setNormalVertex(vertices);
  }
  if (facets.size() > 1) {
    NormalizeParameters::remDuplicateFaces(facets);
  }
}
Figure::Figure(const Figure &f) {
  std::unordered_map<const Vertex *, int> v_map;

  vertices.clear();
  vertices.reserve(f.vertices.size());
  for (qsizetype i = 0; i < f.vertices.size(); i++) {
    vertices.emplace_back(f.vertices[i]);
    v_map[&f.vertices[i]] = i;
  }

  facets.clear();
  facets.reserve(f.facets.size());
  for (qsizetype i = 0; i < f.facets.size(); i++) {
    const Vertex *begin = f.facets[i].getBeginPosition();
    const Vertex *end = f.facets[i].getEndPosition();
    auto index_begin = v_map.find(begin);
    auto index_end = v_map.find(end);
    if (index_begin != v_map.end() && index_end != v_map.end()) {
      facets.emplace_back(&vertices[index_begin->second],
                          &vertices[index_end->second]);
    } else {
      throw "Error: vertex not found";
    }
  }
}

Figure &Figure::operator=(const Figure &f) {
  if (this != &f) {
    std::unordered_map<const Vertex *, int> v_map;

    vertices.clear();
    vertices.reserve(f.vertices.size());
    for (qsizetype i = 0; i < f.vertices.size(); i++) {
      vertices.emplace_back(f.vertices[i]);
      v_map[&f.vertices[i]] = i;
    }

    facets.clear();
    facets.reserve(f.facets.size());
    for (qsizetype i = 0; i < f.facets.size(); i++) {
      const Vertex *begin = f.facets[i].getBeginPosition();
      const Vertex *end = f.facets[i].getEndPosition();
      auto index_begin = v_map.find(begin);
      auto index_end = v_map.find(end);
      if (index_begin != v_map.end() && index_end != v_map.end()) {
        facets.emplace_back(&vertices[index_begin->second],
                            &vertices[index_end->second]);
      } else {
        throw "Error: vertex not found";
      }
    }
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