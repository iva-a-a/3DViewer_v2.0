#pragma once

#include "../model/model.h"
#include <QPainter>
#include <QWidget>

namespace s21 {
class PaintModel : public QWidget {
  Q_OBJECT
private:
  ObjModel *model; // Экземпляр объекта модели

public:
  PaintModel(QWidget *parent = nullptr) : QWidget(parent){};
  ~PaintModel(){};

  void setModel(ObjModel &m) { model = &m; }

  // void setVertices(const QVector<QVector3D> vertices);
  // void setFacets(const QVector<QVector<int>> facets);

  // void loadModel(const QString &filename);

protected:
  void paintEvent(QPaintEvent *event) override;
};
} // namespace s21
