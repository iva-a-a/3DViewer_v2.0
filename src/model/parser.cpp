#include "parser.h"

#include <QRegularExpression>
#include <QTextStream>

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
  while (!text.atEnd()) {
    QString str1 = text.readLine();
    QStringList str2 = str1.split(' ', Qt::SkipEmptyParts);
    if (!str2.isEmpty() && str2[0] == "v") {
      saveCoordVertices(str2, vertices);
    }
  }

  file.seek(0);
  while (!text.atEnd()) {
    QString str1 = text.readLine();
    QStringList str2 = str1.split(' ', Qt::SkipEmptyParts);
    if (!str2.isEmpty() && str2[0] == "f") {
      saveRefFacets(str2, facets, vertices);
    }
  }
  file.close();
}

void Parser::saveCoordVertices(QStringList str, QVector<Vertex> &vertices) {
  if (str.size() >= 4) {
    bool conversionOkX, conversionOkY, conversionOkZ;
    float x = str[1].toFloat(&conversionOkX);
    float y = str[2].toFloat(&conversionOkY);
    float z = str[3].toFloat(&conversionOkZ);
    if (conversionOkX && conversionOkY && conversionOkZ) {
      Vertex v(x, y, z);
      vertices.append(v);
    }
  }
}

void Parser::saveRefFacets(QStringList str, QVector<Edge> &facets,
                           QVector<Vertex> &vertices) {
  if (str.size() >= 4) {
    QVector<int> index;
    bool validIndices = true;

    for (int i = 1; i < str.size(); i++) {
      QStringList str_index = str[i].split('/');
      if (!str_index.isEmpty()) {
        int vertexIndex = str_index[0].toInt() - 1;
        if (vertexIndex >= 0 && vertexIndex < vertices.size()) {
          index.append(vertexIndex);
        } else {
          validIndices = false;
          break;
        }
      }
    }
    if (validIndices && index.size() >= 2) {
      for (int i = 0; i < index.size(); i++) {
        int beginIndex = index[i];
        int endIndex = index[(i + 1) % index.size()];
        Edge edge(&vertices[beginIndex], &vertices[endIndex]);
        facets.append(edge);
      }
    }
  }
}