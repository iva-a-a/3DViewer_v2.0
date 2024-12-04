#include "view/paintviewer.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QString filename = "tv.obj";
  s21::Figure tv(filename);

  s21::PaintViewer window;
  window.setModel(tv);
  window.resize(1700, 900);
  window.setWindowTitle("3D");
  window.show();

  return app.exec();
}