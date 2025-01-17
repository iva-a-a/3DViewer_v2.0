#include "paint_model.h"

using namespace s21;

#define FOCUS 100
#define SCALE 10
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
        startPoint.setX(edge.getBeginPosition()->x() * FOCUS + WIDHT);
        startPoint.setY(-edge.getBeginPosition()->y() * FOCUS + HEIGHT);
        endPoint.setX(edge.getEndPosition()->x() * FOCUS + WIDHT);
        endPoint.setY(-edge.getEndPosition()->y() * FOCUS + HEIGHT);
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

  // вершины не соответствуеют при разных проекциях !!!!
  painter.setBrush(QBrush(s.sett_v.color_vertex));
  for (const Vertex &v : controller->getFigure()->getVertices()) {
    QPointF point(v.x() * FOCUS + WIDHT, -v.y() * FOCUS + HEIGHT);
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