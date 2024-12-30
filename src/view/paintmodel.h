#pragma once

#include "../controller/controller.h"
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

namespace s21 {

enum class ProjectionType { Parallel, Central };

struct SettingVertex {
  enum class Type { Circle, Square, None };
  Type type_vertex = Type::Circle;
  QColor color_vertex = Qt::black;
  int size_vertex = 1;
};
struct SettingLines {
  enum class Type { Solid, Dashed };
  Type type_lines = Type::Solid;
  QColor color_lines = Qt::black;
  int line_thickness = 1;
};

struct RenderSetting {
  // ProjectionType type_projection =
  //     ProjectionType::Parallel; // ВОЗМОЖНО ПЕРЕНЕСТИ В КОНТРОЛЛЕР?????
  SettingVertex sett_v = {};
  SettingLines sett_l = {};
  QColor color_background = Qt::white;
};

class PaintModel : public QWidget {
  Q_OBJECT
private:
  Facade *controller;
  RenderSetting s;
  void resetSetting();

public:
  PaintModel(QWidget *parent, Facade *c) : QWidget(parent), controller(c) {
    s = {};
  };
  ~PaintModel() = default;

  void onMove(float x, float y, float z);
  void onRotate(float x, float y, float z);
  void onScale(float x, float y, float z);
  void onReset();

  size_t onGetSizeVertices() { return controller->getSizeVertices(); }
  size_t onGetSizeFacets() { return controller->getSizeFacets(); }

  void onLoadModel(const QString &filename);

  // Parameters getParamController();

  RenderSetting *getSettingPaint();

protected:
  void paintEvent(QPaintEvent *event) override;
};
} // namespace s21
