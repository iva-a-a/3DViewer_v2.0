#pragma once

#include "../model/figure.h"

namespace s21 {

enum class ProjectionType { Parallel, Central };

struct Parameters {
  QString filename = "";
  float shift_x = 0.0f;
  float shift_y = 0.0f;
  float shift_z = 0.0f;
  float rotate_x = 0.0f;
  float rotate_y = 0.0f;
  float rotate_z = 0.0f;
  float scale = 1.0f;
  ProjectionType type_projection = ProjectionType::Parallel;
};

class Facade {
private:
  Figure model;
  Figure copy_model;
  Parameters p;

  float degreesInRadians(float x);
  void resetParam();

public:
  Facade() { p = {}; }
  ~Facade() = default;

  void moveFigure(float x, float y, float z);
  void rotateFigure(float x, float y, float z);
  void scaleFigure(float x, float y, float z);
  void resetMovement();
  void loadFile(const QString &filename);

  // void loadFileWithSettings();

  Figure *getFigure();
  size_t getSizeVertices();
  size_t getSizeFacets();
  Parameters *getParam();
};

} // namespace s21
