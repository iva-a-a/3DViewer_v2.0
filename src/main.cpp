#include "view/paintviewer.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::ObjModel tv;
  QString filename = "tv.obj";
  tv.recordCoordFromFile(filename);

  s21::PaintViewer window;
  window.setModel(tv);
  window.resize(1700, 900);
  window.setWindowTitle("3D");
  window.show();

  return app.exec();
}