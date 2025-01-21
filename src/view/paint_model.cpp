#include "paint_model.h"

using namespace s21;

#define FOCUS 20
#define SCALE 150
#define WIDHT width() / 2
#define HEIGHT height() / 2

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
void PaintModel::onReset() {
  controller->resetParam();
  resetSetting();
  update();
}

void PaintModel::onLoadModel(const QString &filename) {
  controller->loadFile(filename);
  update();
}

void PaintModel::paintVertex(QPainter &painter, const QPointF &point) const {
  painter.setPen(Qt::NoPen);
  if (s.sett_v.type_vertex == SettingVertex::Type::Circle) {
    painter.drawEllipse(point, s.sett_v.size_vertex / 2,
                        s.sett_v.size_vertex / 2);
  } else if (s.sett_v.type_vertex == SettingVertex::Type::Square) {
    painter.drawRect(point.x() - s.sett_v.size_vertex / 2,
                     point.y() - s.sett_v.size_vertex / 2, s.sett_v.size_vertex,
                     s.sett_v.size_vertex);
  }
}
QPointF PaintModel::projectPoint(const Vertex *position) const {
  float x, y;
  if (controller->getParam()->type_projection == ProjectionType::Parallel) {
    x = position->x() * SCALE + WIDHT;
    y = -position->y() * SCALE + HEIGHT;
  } else {
    if (position->z() == -FOCUS) {
      return QPointF();
    }
    x = (position->x() * FOCUS) / (position->z() + FOCUS) * SCALE + WIDHT;
    y = (-position->y() * FOCUS) / (position->z() + FOCUS) * SCALE + HEIGHT;
  }
  return QPointF(x, y);
}
void PaintModel::paintEvent(QPaintEvent *event) {
  (void)event;
  QPainter painter(this);
  QPen pen;
  painter.fillRect(rect(), s.color_background);

  pen.setColor(s.sett_l.color_lines);
  if (s.sett_l.type_lines == SettingLines::Type::Dashed) {
    pen.setDashPattern({8, 16});
  } else {
    pen.setStyle(Qt::SolidLine);
  }
  pen.setWidth(qMax(s.sett_l.line_thickness, 1));
  painter.setPen(pen);
  if (s.sett_l.line_thickness > 0) {
    for (const Edge &edge : controller->getFigure()->getFacets()) {
      QPointF startPoint = projectPoint(edge.getBeginPosition());
      QPointF endPoint = projectPoint(edge.getEndPosition());
      if (!startPoint.isNull() && !endPoint.isNull()) {
        painter.drawLine(startPoint, endPoint);
      }
    }
  }

  painter.setBrush(QBrush(s.sett_v.color_vertex));
  for (const Vertex &v : controller->getFigure()->getVertices()) {
    QPointF point = projectPoint(&v);
    if (!point.isNull()) {
      paintVertex(painter, point);
    }
    painter.setPen(pen);
  }
}

Parameters *PaintModel::getParamController() { return controller->getParam(); }

RenderSetting *PaintModel::getSettingPaint() { return &s; };

void PaintModel::resetSetting() { s = {}; }