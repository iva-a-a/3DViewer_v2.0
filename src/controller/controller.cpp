#include "controller.h"

#define STEP 5
#include <cmath>

using namespace s21;

float Facade::degreesInRadians(float x) { return x * M_PI / 180.0f; }

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
      degreesInRadians(x - p.rotate_x), degreesInRadians(y - p.rotate_y),
      degreesInRadians(z - p.rotate_z)));

  model.transform(TransformMatrixBuilder::createMoveMatrix(
      p.shift_x / STEP, p.shift_y / STEP, p.shift_z / STEP));
  p.rotate_x = x;
  p.rotate_y = y;
  p.rotate_z = z;
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
  p = {};
}

size_t Facade::getSizeVertices() { return model.getVertices().size(); }
size_t Facade::getSizeFacets() { return model.getFacets().size(); }

// Parameters Facade::getParam() { return p; }
