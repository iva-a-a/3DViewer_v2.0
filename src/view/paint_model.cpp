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
      QPointF startPoint;
      QPointF endPoint;
      if (controller->getParam()->type_projection == ProjectionType::Parallel) {
        startPoint.setX(edge.getBeginPosition()->x() * SCALE + WIDHT);
        startPoint.setY(-edge.getBeginPosition()->y() * SCALE + HEIGHT);
        endPoint.setX(edge.getEndPosition()->x() * SCALE + WIDHT);
        endPoint.setY(-edge.getEndPosition()->y() * SCALE + HEIGHT);
      } else {
        startPoint.setX((edge.getBeginPosition()->x() * FOCUS) /
                            (edge.getBeginPosition()->z() + FOCUS) * SCALE +
                        WIDHT);
        startPoint.setY((-edge.getBeginPosition()->y() * FOCUS) /
                            (edge.getBeginPosition()->z() + FOCUS) * SCALE +
                        HEIGHT);
        endPoint.setX((edge.getEndPosition()->x() * FOCUS) /
                          (edge.getEndPosition()->z() + FOCUS) * SCALE +
                      WIDHT);
        endPoint.setY((-edge.getEndPosition()->y() * FOCUS) /
                          (edge.getEndPosition()->z() + FOCUS) * SCALE +
                      HEIGHT);
      }
      painter.drawLine(startPoint, endPoint);
    }
  }
  painter.setBrush(QBrush(s.sett_v.color_vertex));
  for (const Vertex &v : controller->getFigure()->getVertices()) {
    QPointF point;
    if (controller->getParam()->type_projection == ProjectionType::Parallel) {
      point.setX(v.x() * SCALE + WIDHT);
      point.setY(-v.y() * SCALE + HEIGHT);
    } else {
      float x = (v.x() * FOCUS) / (v.z() + FOCUS) * SCALE + WIDHT;
      float y = (-v.y() * FOCUS) / (v.z() + FOCUS) * SCALE + HEIGHT;
      point.setX(x);
      point.setY(y);
    }
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