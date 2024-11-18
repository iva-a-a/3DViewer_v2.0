#pragma once

#include "../model/model.h"
#include "ui_paint.h"
#include <QMainWindow>
#include <QPainter>

#include <QPixmap>
#include <QSlider>
#include <QToolTip>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class PaintViewer : public QMainWindow {
  Q_OBJECT
private:
  ObjModel *model; // Экземпляр объекта модели
  Ui::MainWindow *ui;

public:
  PaintViewer(QMainWindow *parent = nullptr)
      : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
  };
  ~PaintViewer() { delete ui; };

  void setModel(ObjModel &m) { model = &m; }

  // void setVertices(const QVector<QVector3D> vertices);
  // void setFacets(const QVector<QVector<int>> facets);

  // void loadModel(const QString &filename);

protected:
  void paintEvent(QPaintEvent *event) override;
};
} // namespace s21
