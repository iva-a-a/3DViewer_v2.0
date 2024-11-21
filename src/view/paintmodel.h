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
  ~PaintModel(){};

  void setModel(ObjModel &m) { model = &m; }

protected:
  void paintEvent(QPaintEvent *event) override;
};
} // namespace s21
