#pragma once

#include "../model/parser.h"
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

namespace s21 {
class PaintModel : public QWidget {
  Q_OBJECT
private:
  Parser *model;

public:
  PaintModel(QWidget *parent = nullptr) : QWidget(parent){};
  ~PaintModel() = default;

  void setModel(Parser &m);

protected:
  void paintEvent(QPaintEvent *event) override;
};
} // namespace s21
