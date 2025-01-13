#include "paint_viewer.h"

#include "../controller/parser_settings.h"

using namespace s21;

PaintViewer::PaintViewer(QMainWindow *parent, Facade *c) : QMainWindow(parent) {
  ui = new Ui::MainWindow;
  ui->setupUi(this);
  paint_model = new PaintModel(ui->field, c);
  paint_model->setGeometry(
      QRect(0, 0, ui->field->width(), ui->field->height()));

  if (ParserSettings::checkExistFile() == true) {
    set_start_saved_settings();
    //  set_file_name(paint_model->getParamController().filename);
  } else {
    reset_button(); // начальное положение ползунков (если нет загрузочного
                    // файла)
  }
  // initializeTextBox();
  set_number_of_facets();
  set_number_of_vertices();
};

PaintViewer::~PaintViewer() {
  delete ui;
  delete paint_model;
};

void PaintViewer::closeEvent(QCloseEvent *event) {
  ParserSettings::saveSettingsToFile(paint_model->getParamController(),
                                     paint_model->getSettingPaint());
  event->accept();
}

void PaintViewer::set_start_saved_settings() {
  Parameters p =
      ParserSettings::getSettingsFromFile(paint_model->getSettingPaint());
  paint_model->onLoadModel(p.filename);

  on_scrollRotateX_valueChanged(p.rotate_x);
  on_scrollRotateY_valueChanged(p.rotate_y);
  on_scrollRotateZ_valueChanged(p.rotate_z);

  on_scrollShiftX_valueChanged(p.shift_x);
  on_scrollShiftY_valueChanged(p.shift_y);
  on_scrollShiftZ_valueChanged(p.shift_z);

  on_scrollScale_valueChanged(p.scale);

  // ПАРАМЕТРЫ ОТРИСОВКИ МЕНЯЕМ МЕНЮ
  if (paint_model->getSettingPaint()->sett_v.type_vertex ==
      SettingVertex::Type::Circle) {
    ui->typeSelectVertices->setCurrentIndex(0);
  } else if (paint_model->getSettingPaint()->sett_v.type_vertex ==
             SettingVertex::Type::Square) {
    ui->typeSelectVertices->setCurrentIndex(1);
  } else {
    ui->typeSelectVertices->setCurrentIndex(2);
  }
  if (paint_model->getSettingPaint()->sett_l.type_lines ==
      SettingLines::Type::Solid) {
    ui->typeSelectFacets->setCurrentIndex(0);
  } else {
    ui->typeSelectFacets->setCurrentIndex(1);
  }
  ui->thicknessSelectFacets->setValue(
      paint_model->getSettingPaint()->sett_l.line_thickness);
  ui->sizeSelectVerties->setValue(
      paint_model->getSettingPaint()->sett_v.size_vertex);
}

void PaintViewer::updateTextBox(const QString &text, QLineEdit *line,
                                QScrollBar *scroll) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok) {
    scroll->setValue(value);
  }
  if (value > scroll->maximum()) {
    line->setText(QString::number(scroll->maximum()));
  }
  if (value < scroll->minimum()) {
    line->setText(QString::number(scroll->minimum()));
  }
}

void PaintViewer::initializeTextBox() {
  on_scrollShiftX_valueChanged(ui->scrollShiftX->value());
  on_scrollShiftY_valueChanged(ui->scrollShiftY->value());
  on_scrollShiftZ_valueChanged(ui->scrollShiftZ->value());
  on_scrollRotateX_valueChanged(ui->scrollRotateX->value());
  on_scrollRotateY_valueChanged(ui->scrollRotateY->value());
  on_scrollRotateZ_valueChanged(ui->scrollRotateZ->value());
  on_scrollScale_valueChanged(ui->scrollScale->value());
}

void PaintViewer::on_scrollShiftX_valueChanged(int value) {
  ui->boxShiftX->setText(QString::number(value));
  paint_model->onMove(ui->scrollShiftX->value(), ui->scrollShiftY->value(),
                      ui->scrollShiftZ->value());
}

void PaintViewer::on_boxShiftX_textChanged(const QString &text) {
  updateTextBox(text, ui->boxShiftX, ui->scrollShiftX);
}

void PaintViewer::on_scrollShiftY_valueChanged(int value) {
  ui->boxShiftY->setText(QString::number(value));
  paint_model->onMove(ui->scrollShiftX->value(), ui->scrollShiftY->value(),
                      ui->scrollShiftZ->value());
}

void PaintViewer::on_boxShiftY_textChanged(const QString &text) {
  updateTextBox(text, ui->boxShiftY, ui->scrollShiftY);
}

void PaintViewer::on_scrollShiftZ_valueChanged(int value) {
  ui->boxShiftZ->setText(QString::number(value));
  paint_model->onMove(ui->scrollShiftX->value(), ui->scrollShiftY->value(),
                      ui->scrollShiftZ->value());
}

void PaintViewer::on_boxShiftZ_textChanged(const QString &text) {
  updateTextBox(text, ui->boxShiftZ, ui->scrollShiftZ);
}

void PaintViewer::on_scrollRotateX_valueChanged(int value) {

  //  paint_model->onRotate(ui->scrollRotateX->value(),
  //  ui->scrollRotateY->value(),
  //                        ui->scrollRotateZ->value());
  ui->boxRotateX->setText(QString::number(value));
  paint_model->onRotate(ui->scrollRotateX->value(),
                        paint_model->getParamController()->rotate_y,
                        paint_model->getParamController()->rotate_z);
}

void PaintViewer::on_boxRotateX_textChanged(const QString &text) {
  updateTextBox(text, ui->boxRotateX, ui->scrollRotateX);
}

void PaintViewer::on_scrollRotateY_valueChanged(int value) {
  ui->boxRotateY->setText(QString::number(value));
  // paint_model->onRotate(ui->scrollRotateX->value(),
  // ui->scrollRotateY->value(),
  //                       ui->scrollRotateZ->value());
  paint_model->onRotate(paint_model->getParamController()->rotate_x,
                        ui->scrollRotateY->value(),
                        paint_model->getParamController()->rotate_z);
}

void PaintViewer::on_boxRotateY_textChanged(const QString &text) {
  updateTextBox(text, ui->boxRotateY, ui->scrollRotateY);
}

void PaintViewer::on_scrollRotateZ_valueChanged(int value) {
  ui->boxRotateZ->setText(QString::number(value));
  // paint_model->onRotate(ui->scrollRotateX->value(),
  // ui->scrollRotateY->value(),
  //                       ui->scrollRotateZ->value());
  paint_model->onRotate(paint_model->getParamController()->rotate_x,
                        paint_model->getParamController()->rotate_y,
                        ui->scrollRotateZ->value());
}

void PaintViewer::on_boxRotateZ_textChanged(const QString &text) {
  updateTextBox(text, ui->boxRotateZ, ui->scrollRotateZ);
}

void PaintViewer::on_scrollScale_valueChanged(int value) {
  ui->boxScale->setText(QString::number(value));
  paint_model->onScale(value, value, value);
}

void PaintViewer::on_boxScale_textChanged(const QString &text) {
  updateTextBox(text, ui->boxScale, ui->scrollScale);
}

void PaintViewer::on_thicknessSelectFacets_valueChanged() {
  QToolTip::showText(QCursor::pos(),
                     QString::number(ui->thicknessSelectFacets->value()), this);
  paint_model->getSettingPaint()->sett_l.line_thickness =
      ui->thicknessSelectFacets->value();
  paint_model->update();
}

void PaintViewer::on_sizeSelectVerties_valueChanged() {
  QToolTip::showText(QCursor::pos(),
                     QString::number(ui->sizeSelectVerties->value()), this);
  paint_model->getSettingPaint()->sett_v.size_vertex =
      ui->sizeSelectVerties->value();
  paint_model->update();
}

void PaintViewer::on_typeSelectFacets_currentIndexChanged(int index) {
  if (index == 0) {
    paint_model->getSettingPaint()->sett_l.type_lines =
        SettingLines::Type::Solid;
  } else if (index == 1) {
    paint_model->getSettingPaint()->sett_l.type_lines =
        SettingLines::Type::Dashed;
  }
  paint_model->update();
}

void PaintViewer::on_typeSelectVertices_currentIndexChanged(int index) {
  if (index == 0) {
    paint_model->getSettingPaint()->sett_v.type_vertex =
        SettingVertex::Type::Circle;
  } else if (index == 1) {
    paint_model->getSettingPaint()->sett_v.type_vertex =
        SettingVertex::Type::Square;
  } else if (index == 2) {
    paint_model->getSettingPaint()->sett_v.type_vertex =
        SettingVertex::Type::None;
  }
  paint_model->update();
}

void PaintViewer::on_colorSelectFacets_pressed() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет ребер");

  if (color.isValid()) {
    paint_model->getSettingPaint()->sett_l.color_lines = color;
    paint_model->update();
  }
}

void PaintViewer::on_colorSelectVertices_pressed() {
  QColor color =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет вершин");

  if (color.isValid()) {
    paint_model->getSettingPaint()->sett_v.color_vertex = color;
    paint_model->update();
  }
}

void PaintViewer::on_colorSelectBackground_pressed() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");

  if (color.isValid()) {
    paint_model->getSettingPaint()->color_background = color;
    paint_model->update();
  }
}

void PaintViewer::on_resetSettings_pressed() {
  paint_model->onReset();
  reset_button();
}

void PaintViewer::reset_button() {
  on_boxShiftX_textChanged("0");
  on_boxShiftY_textChanged("0");
  on_boxShiftZ_textChanged("0");

  on_boxRotateX_textChanged("0");
  on_boxRotateY_textChanged("0");
  on_boxRotateZ_textChanged("0");

  on_boxScale_textChanged("1");
  ui->typeSelectVertices->setCurrentIndex(0);
  ui->typeSelectFacets->setCurrentIndex(0);
  ui->thicknessSelectFacets->setValue(1);
  ui->sizeSelectVerties->setValue(1);
}

void PaintViewer::on_chooseFile_pressed() {
  QString dir = QDir::currentPath() + "/models_3d";
  QString filePath = QFileDialog::getOpenFileName(
      this, tr("Выберите файл"), dir, tr("Файлы 3D моделей (*.obj)"));
  if (filePath.isEmpty()) {
    QMessageBox::warning(this, tr("Ошибка"), tr("Файл не выбран"));
  }

  paint_model->onLoadModel(filePath);
  set_number_of_facets();
  set_number_of_vertices();
  QString fileName = QFileInfo(filePath).fileName();
  set_file_name(fileName);
  on_resetSettings_pressed();
}

void PaintViewer::on_saveAsBmpOrJpeg_pressed() {
  QString format;
  QDir dir("saved_images");
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Сохранить изображение"), dir.absolutePath(),
      tr("BMP (*.bmp);; JPEG (*.jpeg)"), &format);

  if (!fileName.isEmpty()) {
    QRect rect(10, 10, ui->field->width(), ui->field->height());
    QPixmap image = QWidget::grab(rect);

    QStringList formatList = format.split(";");
    QString extension = fileName.section('.', -1);
    QString imageFormat = formatList.contains("BMP (*.bmp)") ? "bmp" : "jpeg";
    if (extension != imageFormat) {
      fileName += "." + imageFormat;
    }
    image.save(fileName, imageFormat.toLatin1().constData());
  } else {
    QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось сохранить файл"));
  }
}

void PaintViewer::on_saveAsGif_pressed() {}

void PaintViewer::set_number_of_facets() {
  ui->number_of_edges->setPlainText(
      QString::number(paint_model->onGetSizeFacets()));
}

void PaintViewer::set_number_of_vertices() {
  ui->number_of_vertices->setPlainText(
      QString::number(paint_model->onGetSizeVertices()));
}

void PaintViewer::set_file_name(const QString &filename) {
  ui->fileName->setPlainText(filename);
}