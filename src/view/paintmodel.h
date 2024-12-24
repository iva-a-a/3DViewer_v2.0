#pragma once
// #include "../model/figure.h"
#include "../controller/controller.h"
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

namespace s21 {
class PaintModel : public QWidget {
  Q_OBJECT
private:
  Facade *controller;

public:
  PaintModel(QWidget *parent, Facade *c) : QWidget(parent), controller(c) {};
  ~PaintModel() = default;

  void onMove(float x, float y, float z);
  void onRotate(float x, float y, float z);
  void onScale(float x, float y, float z);
  void onReset();

  // Parameters getParamController();

  // void setX(float x) { controller->setRotateX(x); }
  // void setY(float y) { controller->setRotateY(y); }
  // void setZ(float z) { controller->setRotateZ(z); }

protected:
  void paintEvent(QPaintEvent *event) override;
};
} // namespace s21
