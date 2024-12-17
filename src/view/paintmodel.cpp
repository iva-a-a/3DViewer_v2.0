#include "paintmodel.h"

using namespace s21;

void PaintModel::onMove(float x, float y, float z) {
  controller->moveFigure(x, y, z);
  update();
}

void PaintModel::onRotate(float x, float y, float z) {
  controller->rotateFigure(x, y, z);
  update();
}

void PaintModel::onScale(float x, float y, float z) {
  controller->scaleFigure(x, y, z);
  update();
}

void PaintModel::paintEvent(QPaintEvent *event) {

  (void)event;
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QPen pen(Qt::red, 5);
  painter.setPen(pen);

  for (const Vertex &v : controller->getFigure()->getVertices()) {
    QPointF point(v.x() * 100 + width() / 2, -v.y() * 100 + height() / 2);
    painter.drawPoint(point);
  }

  pen.setColor(Qt::black);
  pen.setWidth(1);
  painter.setPen(pen);

  for (const Edge &edge : controller->getFigure()->getFacets()) {
    const QPointF startPoint(edge.getBeginPosition().x() * 100 + width() / 2,
                             -edge.getBeginPosition().y() * 100 + height() / 2);
    const QPointF endPoint(edge.getEndPosition().x() * 100 + width() / 2,
                           -edge.getEndPosition().y() * 100 + height() / 2);
    painter.drawLine(startPoint, endPoint);
  }
}