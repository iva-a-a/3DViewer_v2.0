#include "parser.h"

#include <QRegularExpression>
#include <QTextStream>

using namespace s21;

void Parser::recordCoordFromFile(const QString &filename,
                                 QVector<Vertex> &vertices,
                                 QVector<Edge> &facets) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    throw std::runtime_error("Cannot open file: " + filename.toStdString());
  }

  vertices.clear();
  facets.clear();

  QTextStream text(&file);

  // Чтение вершин
  while (!text.atEnd()) {
    QString line = text.readLine().trimmed();
    if (line.startsWith("v ")) {
      QStringList parts = line.split(' ', Qt::SkipEmptyParts);
      try {
        saveCoordVertices(parts, vertices);
      } catch (const std::exception &e) {
        throw std::runtime_error("Error parsing vertex: " + line.toStdString() + ". " + e.what());
      }
    }
  }

  // Сбрасываем позицию файла для повторного чтения
  file.seek(0);

  // Чтение граней
  while (!text.atEnd()) {
    QString line = text.readLine().trimmed();
    if (line.startsWith("f ")) {
      QStringList parts = line.split(' ', Qt::SkipEmptyParts);
      try {
        saveRefFacets(parts, facets, vertices);
      } catch (const std::exception &e) {
        throw std::runtime_error("Error parsing face: " + line.toStdString() + ". " + e.what());
      }
    }
  }

  file.close();
}

void Parser::saveCoordVertices(QStringList str, QVector<Vertex> &vertices) {
  if (str.size() != 4) {
    throw std::runtime_error("Invalid vertex format: " + str.join(' ').toStdString());
  }

  bool okX, okY, okZ;
  float x = str[1].toFloat(&okX);
  float y = str[2].toFloat(&okY);
  float z = str[3].toFloat(&okZ);

  if (!okX || !okY || !okZ) {
    throw std::runtime_error("Invalid vertex coordinates: " + str.join(' ').toStdString());
  }

  Vertex v(x, y, z);
  vertices.append(v);
}

void Parser::saveRefFacets(QStringList str, QVector<Edge> &facets, QVector<Vertex> &vertices) {
  if (str.size() < 4) {
    throw std::runtime_error("Invalid face format: " + str.join(' ').toStdString());
  }

  QVector<int> indices;
  for (int i = 1; i < str.size(); i++) {
    QStringList parts = str[i].split('/');
    bool ok;
    int index = parts[0].toInt(&ok) - 1; // Индексы в OBJ начинаются с 1
    if (!ok || index < 0 || index >= vertices.size()) {
      throw std::runtime_error("Invalid face index: " + str[i].toStdString());
    }
    indices.append(index);
  }

  for (int i = 0; i < indices.size(); i++) {
    int beginIndex = indices[i];
    int endIndex = indices[(i + 1) % indices.size()];
    Edge edge(&vertices[beginIndex], &vertices[endIndex]);
    facets.append(edge);
  }
}
