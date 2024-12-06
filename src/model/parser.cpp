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
  while (!text.atEnd()) {
    QString str1 = text.readLine();
    QStringList str2 = str1.split(' ', Qt::SkipEmptyParts);
    if (!str2.isEmpty()) {
      if (str2[0] == "v") {
        saveCoordVertices(str2, vertices);
      } else if (str2[0] == "f") {
        saveRefFacets(str2, facets, vertices);
      }
    }
  }
  file.close();
}

void Parser::saveCoordVertices(QStringList str, QVector<Vertex> &vertices) {
  if (str.size() >= 4) {
    Vertex v(str[1].toFloat(), str[2].toFloat(), str[3].toFloat());
    vertices.append(v);
  }
}
void Parser::saveRefFacets(QStringList str, QVector<Edge> &facets,
                           QVector<Vertex> &vertices) {
  if (str.size() >= 4) {
    // Сохраняем индексы вершин
    QVector<int> index;
    for (int i = 1; i < str.size(); i++) {
      QStringList str_index = str[i].split('/');
      if (!str_index.isEmpty()) {
        index.append(str_index[0].toInt() - 1);
      }
    }
    // Создаем ребра для грани, используя индексы
    for (int i = 0; i < index.size(); i++) {
      int beginIndex = index[i];
      int endIndex =
          index[(i + 1) % index.size()]; // Соединяем последний с первым

      // Создаем ребро, используя ссылки на вершины
      Edge edge(vertices[beginIndex], vertices[endIndex]);
      facets.append(edge);
    }
  }
}