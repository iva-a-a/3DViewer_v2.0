#pragma once

#include "ui_paint.h"
#include <QCloseEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QSlider>
#include <QToolTip>

#include "paint_model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
} // namespace Ui
QT_END_NAMESPACE

namespace s21 {

class PaintViewer : public QMainWindow {
  Q_OBJECT
private:
  Ui::MainWindow *ui;
  PaintModel *paint_model;

public:
  PaintViewer(QMainWindow *parent, Facade *c);
  ~PaintViewer();

  void closeEvent(QCloseEvent *event) override;

private slots:

  void on_scrollShiftX_valueChanged(int value);
  void on_boxShiftX_textChanged(const QString &text);
  void on_scrollShiftY_valueChanged(int value);
  void on_boxShiftY_textChanged(const QString &text);
  void on_scrollShiftZ_valueChanged(int value);
  void on_boxShiftZ_textChanged(const QString &text);

  void on_scrollRotateX_valueChanged(int value);
  void on_boxRotateX_textChanged(const QString &text);
  void on_scrollRotateY_valueChanged(int value);
  void on_boxRotateY_textChanged(const QString &text);
  void on_scrollRotateZ_valueChanged(int value);
  void on_boxRotateZ_textChanged(const QString &text);

  void on_scrollScale_valueChanged(int value);
  void on_boxScale_textChanged(const QString &text);

  void on_thicknessSelectFacets_valueChanged();
  void on_typeSelectFacets_currentIndexChanged(int index);
  void on_colorSelectFacets_pressed();

  void on_sizeSelectVerties_valueChanged();
  void on_typeSelectVertices_currentIndexChanged(int index);
  void on_colorSelectVertices_pressed();

  void on_colorSelectBackground_pressed();

  void on_chooseFile_pressed();
  void on_resetSettings_pressed();

  void on_saveAsBmpOrJpeg_pressed();
  void on_saveAsGif_pressed();

private:
  void updateTextBox(const QString &text, QLineEdit *line, QScrollBar *scroll);
  void initializeTextBox();
  void set_number_of_facets();
  void set_number_of_vertices();
  void set_file_name(const QString &filename);
  void reset_button();
  void set_start_saved_settings();
};
} // namespace s21