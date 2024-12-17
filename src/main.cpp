#include "view/paintviewer.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QString filename = "tv.obj";
  s21::Facade scene(filename);

  s21::PaintViewer window(nullptr, &scene);

  window.resize(1700, 900);
  window.setWindowTitle("3D");
  window.show();

  return app.exec();
}