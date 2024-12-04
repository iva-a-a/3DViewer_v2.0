#pragma once

#include "../model/figure.h"
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

namespace s21 {
class PaintModel : public QWidget {
  Q_OBJECT
private:
  Figure *model;

public:
  PaintModel(QWidget *parent = nullptr) : QWidget(parent) {};
  ~PaintModel() = default;

  void setModel(Figure &m);

protected:
  void paintEvent(QPaintEvent *event) override;
};
} // namespace s21
