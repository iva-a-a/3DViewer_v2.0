#pragma once

// #include "../model/model.h"
#include "ui_paint.h"
#include <QMainWindow>
#include <QPainter>

#include <QPixmap>
#include <QSlider>
#include <QToolTip>

#include "paintmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class PaintViewer : public QMainWindow {
  Q_OBJECT
private:
  Ui::MainWindow *ui;
  PaintModel *paint_model;

public:
  PaintViewer(QMainWindow *parent = nullptr)
      : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    paint_model = new PaintModel(ui->field);
    paint_model->setGeometry(
        QRect(0, 0, ui->field->width() - 10, ui->field->height() - 10));
  };
  ~PaintViewer() {
    delete ui;
    delete paint_model;
  };

  void setModel(ObjModel &m) { paint_model->setModel(m); }
};
} // namespace s21