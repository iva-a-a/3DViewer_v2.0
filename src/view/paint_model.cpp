#include "paint_model.h"

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
void PaintModel::onReset() {
  controller->resetParam();
  resetSetting();
  update();
}

void PaintModel::onLoadModel(const QString &filename) {
  controller->loadFile(filename);
  update();
}

void PaintModel::paintEvent(QPaintEvent *event) {
  (void)event;
  QPainter painter(this);
  painter.fillRect(rect(), s.color_background);

  QPen pen;
  pen.setColor(s.sett_l.color_lines);
  if (s.sett_l.type_lines == SettingLines::Type::Dashed) {
    QList<qreal> dashes;
    dashes << 8 << 16;
    pen.setDashPattern(dashes);
  } else {
    pen.setStyle(Qt::SolidLine);
  }
  if (s.sett_l.line_thickness > 0) {
    pen.setWidth(s.sett_l.line_thickness);
  }
  painter.setPen(pen);
  if (s.sett_l.line_thickness > 0) {
    for (const Edge &edge : controller->getFigure()->getFacets()) {
      const QPointF startPoint(edge.getBeginPosition()->x() * 100 + width() / 2,
                               -edge.getBeginPosition()->y() * 100 +
                                   height() / 2);
      const QPointF endPoint(edge.getEndPosition()->x() * 100 + width() / 2,
                             -edge.getEndPosition()->y() * 100 + height() / 2);
      painter.drawLine(startPoint, endPoint);
    }
  }

  painter.setBrush(QBrush(s.sett_v.color_vertex));
  for (const Vertex &v : controller->getFigure()->getVertices()) {
    QPointF point(v.x() * 100 + width() / 2, -v.y() * 100 + height() / 2);
    if (s.sett_v.type_vertex == SettingVertex::Type::Circle) {
      painter.setPen(Qt::NoPen);
      painter.drawEllipse(point, s.sett_v.size_vertex / 2,
                          s.sett_v.size_vertex / 2);
      painter.setPen(pen);
    } else if (s.sett_v.type_vertex == SettingVertex::Type::Square) {
      painter.setPen(Qt::NoPen);
      painter.drawRect(point.x() - s.sett_v.size_vertex / 2,
                       point.y() - s.sett_v.size_vertex / 2,
                       s.sett_v.size_vertex, s.sett_v.size_vertex);
      painter.setPen(pen);
    }
  }
}

Parameters *PaintModel::getParamController() { return controller->getParam(); }

RenderSetting *PaintModel::getSettingPaint() { return &s; };

void PaintModel::resetSetting() { s = {}; }