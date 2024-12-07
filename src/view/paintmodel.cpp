#include "paintmodel.h"

using namespace s21;

void PaintModel::setModel(Figure &m) {
  model = &m;
  model->transform(TransformMatrixBuilder::createRotationMatrix(3, 1, 1));
}

void PaintModel::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QPen pen(Qt::red, 5);
  painter.setPen(pen);

  for (const Vertex &v : model->getVertices()) {
    QPointF point(v.x() * 100 + width() / 2, -v.y() * 100 + height() / 2);
    painter.drawPoint(point);
  }

  // Draw edges
  pen.setColor(Qt::black);
  pen.setWidth(1);
  painter.setPen(pen);

  for (const Edge &edge : model->getFacets()) {
    const QPointF startPoint(edge.getBeginPosition().x() * 100 + width() / 2,
                             -edge.getBeginPosition().y() * 100 + height() / 2);
    const QPointF endPoint(edge.getEndPosition().x() * 100 + width() / 2,
                           -edge.getEndPosition().y() * 100 + height() / 2);
    painter.drawLine(startPoint, endPoint);
  }
}