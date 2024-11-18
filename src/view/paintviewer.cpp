#include "paintviewer.h"

using namespace s21;

// void PaintViewer::setVertices(const QVector<QVector3D> vertices) {
//   v = vertices;
// }
// void PaintViewer::setFacets(const QVector<QVector<int>> facets) { f = facets;
// }

// void PaintViewer::loadModel(const QString &filename) {
//   model->recordCoordFromFile(filename);
//   update();
// }

void PaintViewer::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing); // сглаживание

  //вершины
  QPen pen(Qt::red, 5);
  painter.setPen(pen);
  for (const QVector3D &v : model->getVertices()) {
    QPointF point(v.x() * 50 + width() / 2, -v.y() * 50 + height() / 2);
    painter.drawPoint(point);
  }
  //грани
  pen.setColor(Qt::black);
  pen.setWidth(1);
  painter.setPen(pen);
  for (const QVector<int> &f : model->getFacets()) {
    for (int i = 0; i < f.size(); ++i) {
      const QVector3D &start = model->getVertices()[f[i]];
      const QVector3D &end = model->getVertices()[f[(i + 1) % f.size()]];
      QPointF startPoint(start.x() * 50 + width() / 2,
                         -start.y() * 50 + height() / 2);
      QPointF endPoint(end.x() * 50 + width() / 2,
                       -end.y() * 50 + height() / 2);
      painter.drawLine(startPoint, endPoint);
    }
  }
}