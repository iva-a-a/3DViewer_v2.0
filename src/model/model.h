#pragma once

#include <QFile>
#include <QString>
#include <QVector3D>
#include <QVector>

namespace s21 {

class ObjModel {
private:
  QVector<QVector3D> vertices; // координаты вершин
  QVector<QVector<int>> facets; // индексы вершин, составляющих грани

public:
  // запись координат вершин и граней из файла
  void recordCoordFromFile(const QString &filename);

  ObjModel(){};
  ~ObjModel() = default;

  const QVector<QVector3D> &getVertices();
  const QVector<QVector<int>> &getFacets();
};

} // namespace s21
