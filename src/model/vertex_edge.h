#pragma once
#include <QVector3D>

#include "transform_matrix.h"

namespace s21 {

class Vertex : public QVector3D {
 public:
  Vertex() : QVector3D() {}
  Vertex(float x, float y, float z) : QVector3D(x, y, z) {}
  Vertex(const QVector3D &v) : QVector3D(v) {}
  ~Vertex() = default;

  void transform(const TransformMatrix &m) { *this = m.transformPoint(*this); }
};

class Edge {
 private:
  Vertex *_begin;
  Vertex *_end;

 public:
  Edge(Vertex *begin, Vertex *end) : _begin(begin), _end(end) {}
  ~Edge() = default;

  const Vertex *getBeginPosition() const { return _begin; }
  const Vertex *getEndPosition() const { return _end; }

  bool operator==(const Edge &e) const {
    return (_begin == e._begin && _end == e._end) ||
           (_begin == e._end && _end == e._begin);
  }
  struct HashEdge {
    size_t operator()(const Edge &e) const {
      return std::hash<Vertex *>()(e._begin) ^ std::hash<Vertex *>()(e._end);
    }
  };
};

}  // namespace s21