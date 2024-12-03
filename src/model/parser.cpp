#include "parser.h"

#include <QRegularExpression>
#include <QTextStream>

using namespace s21;

void Parser ::recordCoordFromFile(const QString &filename) {
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
        if (str2.size() >= 4) {
          QVector3D v(str2[1].toFloat(), str2[2].toFloat(), str2[3].toFloat());
          vertices.append(v);
        }
      } else if (str2[0] == "f") {
        if (str2.size() >= 4) {
          QVector<int> f;
          for (int i = 1; i < str2.size(); i++) {
            QStringList str_index = str2[i].split('/');
            if (!str_index.isEmpty()) {
              f.append(str_index[0].toInt() - 1);
            }
          }
          facets.append(f);
        }
      }
    }
  }
  file.close();
}

const QVector<QVector3D> &Parser ::getVertices() { return vertices; }
const QVector<QVector<int>> &Parser ::getFacets() { return facets; }