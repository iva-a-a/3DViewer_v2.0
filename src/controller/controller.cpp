#include "controller.h"

#define STEP 5
#include <cmath>

using namespace s21;

float Facade::degreesInRadians(float x) { return x * M_PI / 180.0f; }

void Facade::resetParam() {
  p.scale = 1.0f;
  p.shift_x = 0.0f;
  p.shift_y = 0.0f;
  p.shift_z = 0.0f;
  p.rotate_x = 0.0f;
  p.rotate_y = 0.0f;
  p.rotate_z = 0.0f;
  p.type_projection = ProjectionType::Parallel;
}

void Facade::loadFile(const QString &filename) {
  if (filename.isEmpty()) {
    return;
  }
  p.filename = filename;
  Figure f(filename);
  model = f;
  copy_model = model;
}

void Facade::moveFigure(float x, float y, float z) {
  model.transform(TransformMatrixBuilder::createMoveMatrix(
      (x - p.shift_x) / STEP, (y - p.shift_y) / STEP, (z - p.shift_z) / STEP));
  p.shift_x = x;
  p.shift_y = y;
  p.shift_z = z;
}

void Facade::rotateFigure(float x, float y, float z) {

  model.transform(TransformMatrixBuilder::createMoveMatrix(
      -p.shift_x / STEP, -p.shift_y / STEP, -p.shift_z / STEP));

  model.transform(TransformMatrixBuilder::createRotationMatrix(
      degreesInRadians(0), degreesInRadians(0), degreesInRadians(-p.rotate_z)));
  model.transform(TransformMatrixBuilder::createRotationMatrix(
      degreesInRadians(0), degreesInRadians(-p.rotate_y), degreesInRadians(0)));
  model.transform(TransformMatrixBuilder::createRotationMatrix(
      degreesInRadians(-p.rotate_x), degreesInRadians(0), degreesInRadians(0)));
  model.transform(TransformMatrixBuilder::createRotationMatrix(
      degreesInRadians(x), degreesInRadians(0), degreesInRadians(0)));
  model.transform(TransformMatrixBuilder::createRotationMatrix(
      degreesInRadians(0), degreesInRadians(y), degreesInRadians(0)));
  model.transform(TransformMatrixBuilder::createRotationMatrix(
      degreesInRadians(0), degreesInRadians(0), degreesInRadians(z)));

  model.transform(TransformMatrixBuilder::createMoveMatrix(
      p.shift_x / STEP, p.shift_y / STEP, p.shift_z / STEP));
  p.rotate_x = x;
  p.rotate_y = y;
  p.rotate_z = z;
  std::cout << "rotatefigure " << p.rotate_x << " " << p.rotate_y << " "
            << p.rotate_z << std::endl;
}

void Facade::scaleFigure(float x, float y, float z) {
  model.transform(TransformMatrixBuilder::createMoveMatrix(
      -p.shift_x / STEP, -p.shift_y / STEP, -p.shift_z / STEP));
  model.transform(TransformMatrixBuilder::createScaleMatrix(
      x / p.scale, y / p.scale, z / p.scale));
  model.transform(TransformMatrixBuilder::createMoveMatrix(
      p.shift_x / STEP, p.shift_y / STEP, p.shift_z / STEP));
  p.scale = x;
}

Figure *Facade::getFigure() { return &model; }

void Facade::resetMovement() {
  model = copy_model;
  resetParam();
}

size_t Facade::getSizeVertices() { return model.getVertices().size(); }
size_t Facade::getSizeFacets() { return model.getFacets().size(); }
Parameters *Facade::getParam() { return &p; }
