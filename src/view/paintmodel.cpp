#include "paintmodel.h"

using namespace s21;

void PaintModel::setModel(Figure &m) { model = &m; }

void PaintModel::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing); // сглаживание

  // вершины
  QPen pen(Qt::red, 5);
  painter.setPen(pen);
  for (const QVector3D &v : model->getVertices()) {
    QPointF point(v.x() * 100 + width() / 2, -v.y() * 100 + height() / 2);
    painter.drawPoint(point);
  }
  // грани
  pen.setColor(Qt::black);
  pen.setWidth(1);
  painter.setPen(pen);
  for (const QVector<int> &f : model->getFacets()) {
    for (int i = 0; i < f.size(); ++i) {
      const QVector3D &start = model->getVertices()[f[i]];
      const QVector3D &end = model->getVertices()[f[(i + 1) % f.size()]];
      QPointF startPoint(start.x() * 100 + width() / 2,
                         -start.y() * 100 + height() / 2);
      QPointF endPoint(end.x() * 100 + width() / 2,
                       -end.y() * 100 + height() / 2);
      painter.drawLine(startPoint, endPoint);
    }
  }
}