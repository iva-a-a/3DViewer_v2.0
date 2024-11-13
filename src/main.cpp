#include "view/paintmodel.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::ObjModel tv;
  QString filename = "tv.obj";
  tv.recordCoordFromFile(filename);

  s21::PaintModel window;
  window.setModel(tv);
  window.resize(800, 600);
  window.setWindowTitle("3D");
  window.show();

  return app.exec();
}