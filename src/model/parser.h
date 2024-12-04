#pragma once

#include "transform_figure.h"

#include <QFile>
#include <QString>

namespace s21 {

class Parser {
public:
  Parser() {};
  ~Parser() = default;
  // запись координат вершин и граней из файла
  static void recordCoordFromFile(const QString &filename,
                                  QVector<QVector3D> &vertices,
                                  QVector<QVector<int>> &facets);
};

} // namespace s21
