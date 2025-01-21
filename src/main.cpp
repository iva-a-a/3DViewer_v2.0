#include <QApplication>

#include "view/paint_viewer.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::Facade scene;
  s21::PaintViewer window(nullptr, &scene);

  window.resize(1580, 885);
  window.setWindowTitle("3D_VIEWER");
  window.show();
  return app.exec();
}