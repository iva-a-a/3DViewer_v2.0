#pragma once

#include "transform_figure.h"

#include <QFile>
#include <QString>

namespace s21 {

class Parser {
private:
  Parser() {};
  ~Parser() = default;
  static void saveCoordVertices(QStringList str, QVector<Vertex> &vertices);
  static void saveRefFacets(QStringList str, QVector<Edge> &facets,
                            QVector<Vertex> &vertices);

public:
  static void recordCoordFromFile(const QString &filename,
                                  QVector<Vertex> &vertices,
                                  QVector<Edge> &facets);
};

} // namespace s21
