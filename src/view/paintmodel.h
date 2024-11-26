#pragma once

#include "../model/model.h"
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

namespace s21 {
class PaintModel : public QWidget {
  Q_OBJECT
private:
  ObjModel *model;

public:
  PaintModel(QWidget *parent = nullptr) : QWidget(parent){};
  ~PaintModel() = default;

  void setModel(ObjModel &m);

protected:
  void paintEvent(QPaintEvent *event) override;
};
} // namespace s21
