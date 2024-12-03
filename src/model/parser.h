#pragma once

#include <QFile>
#include <QString>
#include <QVector3D>
#include <QVector>

namespace s21 {

class Parser {
private:
  QVector<QVector3D> vertices; // координаты вершин
  QVector<QVector<int>> facets; // индексы вершин, составляющих грани

public:
  // запись координат вершин и граней из файла
  void recordCoordFromFile(const QString &filename);

  Parser(){};
  ~Parser() = default;

  const QVector<QVector3D> &getVertices();
  const QVector<QVector<int>> &getFacets();
};

} // namespace s21
