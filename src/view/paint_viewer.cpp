#include "paint_viewer.h"

#include <QDir>
#include <QImage>

#include "../controller/parser_settings.h"

using namespace s21;

PaintViewer::PaintViewer(QMainWindow *parent, Facade *c) : QMainWindow(parent) {
  ui = new Ui::MainWindow;
  ui->setupUi(this);
  paint_model = new PaintModel(ui->field, c);
  paint_model->setGeometry(
      QRect(0, 0, ui->field->width(), ui->field->height()));
  set_onOrOff_buttons(false);

  if (ParserSettings::checkExistFile("settings.txt") == true) {
    set_start_saved_settings();
  } else {
    initialize_text_box();
  }
  set_textToQTextBrowser(ui->number_of_edges, paint_model->onGetSizeFacets());
  set_textToQTextBrowser(ui->number_of_vertices,
                         paint_model->onGetSizeVertices());

  _screencastTimer = new QTimer(this);
  connect(_screencastTimer, &QTimer::timeout, this, &PaintViewer::recordFrame);
  connect(_screencastTimer, &QTimer::timeout, this,
          &PaintViewer::updateCountdown);
};

PaintViewer::~PaintViewer() {
  delete ui;
  delete paint_model;
  delete _screencastTimer;
};

void PaintViewer::closeEvent(QCloseEvent *event) {
  if (paint_model->getParamController()->filename.isEmpty()) {
    return;
  }
  ParserSettings::saveSettingsToFile(paint_model->getParamController(),
                                     paint_model->getSettingPaint());
  event->accept();
}

void PaintViewer::set_start_saved_settings() {
  Parameters p =
      ParserSettings::getSettingsFromFile(paint_model->getSettingPaint());
  if (ParserSettings::checkExistFile(p.filename.toStdString()) == false) {
    return;
  }
  set_onOrOff_buttons(true);
  paint_model->onLoadModel(p.filename);

  set_file_name(get_filename(p.filename));

  if (p.type_projection == ProjectionType::Parallel) {
    ui->typeProjection->setCurrentIndex(0);
  } else {
    ui->typeProjection->setCurrentIndex(1);
  }
  paint_model->getParamController()->type_projection = p.type_projection;

  on_scrollShiftX_valueChanged(p.shift_x);
  on_scrollShiftY_valueChanged(p.shift_y);
  on_scrollShiftZ_valueChanged(p.shift_z);

  on_scrollRotateX_valueChanged(p.rotate_x);
  on_scrollRotateY_valueChanged(p.rotate_y);
  on_scrollRotateZ_valueChanged(p.rotate_z);
  on_scrollScale_valueChanged(p.scale);

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

void PaintViewer::initialize_text_box() {
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
  paint_model->onRotate(paint_model->getParamController()->rotate_x,
                        ui->scrollRotateY->value(),
                        paint_model->getParamController()->rotate_z);
}

void PaintViewer::on_boxRotateY_textChanged(const QString &text) {
  updateTextBox(text, ui->boxRotateY, ui->scrollRotateY);
}

void PaintViewer::on_scrollRotateZ_valueChanged(int value) {
  ui->boxRotateZ->setText(QString::number(value));
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

void PaintViewer::on_typeProjection_currentIndexChanged(int index) {
  if (index == 0) {
    paint_model->getParamController()->type_projection =
        ProjectionType::Parallel;

  } else {
    paint_model->getParamController()->type_projection =
        ProjectionType::Central;
  }
  paint_model->update();
}

void PaintViewer::on_resetSettings_pressed() {
  on_scrollShiftX_valueChanged(0);
  on_scrollShiftY_valueChanged(0);
  on_scrollShiftZ_valueChanged(0);

  on_scrollRotateX_valueChanged(0);
  on_scrollRotateY_valueChanged(0);
  on_scrollRotateZ_valueChanged(0);

  on_scrollScale_valueChanged(1);
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
  ui->typeProjection->setCurrentIndex(0);
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
    return;
  }
  set_onOrOff_buttons(true);
  reset_button();
  paint_model->onLoadModel(filePath);
  set_textToQTextBrowser(ui->number_of_edges, paint_model->onGetSizeFacets());
  set_textToQTextBrowser(ui->number_of_vertices,
                         paint_model->onGetSizeVertices());
  QString fileName = get_filename(filePath);
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
    QMessageBox::information(this, "SAVED AS BMP/JPG ",
                             "Изображение сохранено в " + fileName);
  } else {
    QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось сохранить файл"));
  }
}

void PaintViewer::set_textToQTextBrowser(QTextBrowser *text,
                                         const size_t size) {
  text->setPlainText(QString::number(size));
}

void PaintViewer::set_file_name(const QString &filename) {
  ui->fileName->setPlainText(filename);
}

QString PaintViewer::get_filename(const QString &filePath) {
  QFileInfo fileInfo(filePath);
  return fileInfo.fileName();
}

void PaintViewer::set_onOrOff_buttons(bool enabled) {
  ui->scrollRotateX->setEnabled(enabled);
  ui->scrollRotateY->setEnabled(enabled);
  ui->scrollRotateZ->setEnabled(enabled);
  ui->scrollShiftX->setEnabled(enabled);
  ui->scrollShiftY->setEnabled(enabled);
  ui->scrollShiftZ->setEnabled(enabled);
  ui->scrollScale->setEnabled(enabled);

  ui->typeProjection->setEnabled(enabled);

  ui->resetSettings->setEnabled(enabled);

  ui->boxShiftX->setEnabled(enabled);
  ui->boxShiftY->setEnabled(enabled);
  ui->boxShiftZ->setEnabled(enabled);
  ui->boxRotateX->setEnabled(enabled);
  ui->boxRotateY->setEnabled(enabled);
  ui->boxRotateZ->setEnabled(enabled);
  ui->boxScale->setEnabled(enabled);

  ui->thicknessSelectFacets->setEnabled(enabled);
  ui->typeSelectFacets->setEnabled(enabled);
  ui->colorSelectFacets->setEnabled(enabled);

  ui->sizeSelectVerties->setEnabled(enabled);
  ui->typeSelectVertices->setEnabled(enabled);
  ui->colorSelectVertices->setEnabled(enabled);

  ui->colorSelectBackground->setEnabled(enabled);

  ui->saveAsBmpOrJpeg->setEnabled(enabled);
  ui->saveAsGif->setEnabled(enabled);
}

void PaintViewer::on_saveAsGif_pressed() {
  _frameCounter = 0;
  _outputDir = "saved_screencasts/";
  QDir dir(_outputDir);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  _screencastTimer->start(100);
}

void PaintViewer::recordFrame() {
  if (_frameCounter < 50) {
    QString filename = QString("%1frame_%2.png")
                           .arg(_outputDir)
                           .arg(_frameCounter, 3, 10, QChar('0'));

    QPixmap pixmap = ui->field->grab();
    QImage frame = pixmap.toImage().scaled(640, 480, Qt::KeepAspectRatio);
    frame.save(filename, "PNG");
    _frameCounter++;
  } else {
    _screencastTimer->stop();

    QString gifFileName = QFileDialog::getSaveFileName(
        this, "Сохранить GIF", _outputDir, "GIF Files (*.gif)");
    if (!gifFileName.isEmpty()) {
      QString gifCommand =
          QString("convert -delay 10 -loop 0 %1frame_*.png \"%2\"")
              .arg(_outputDir)
              .arg(gifFileName);
      (void)system(gifCommand.toStdString().c_str());
      QString cleanupCommand = QString("rm -f %1frame_*.png").arg(_outputDir);
      (void)system(cleanupCommand.toStdString().c_str());
      QMessageBox::information(this, "SAVED AS GIF",
                               "Скринкаст сохранён в " + gifFileName);
    } else {
      QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось сохранить файл"));
    }
  }
}

void PaintViewer::updateCountdown() {
  static int countdown = 50;
  if (countdown > 0) {
    if (countdown % 10 == 0) {
      ui->saveAsGif->setText(QString::number(countdown / 10));
    }
    countdown--;
  }
  if (countdown == 0) {
    ui->saveAsGif->setText("gif");
    countdown = 50;
  }
}
