#include "paintviewer.h"

using namespace s21;

PaintViewer::PaintViewer(QMainWindow *parent, Facade *c) : QMainWindow(parent) {
  ui = new Ui::MainWindow;
  ui->setupUi(this);

  paint_model = new PaintModel(ui->field, c);
  paint_model->setGeometry(
      QRect(0, 0, ui->field->width() - 10, ui->field->height() - 10));
  initializeTextBox();
};

PaintViewer::~PaintViewer() {
  delete ui;
  delete paint_model;
};

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
  ui->boxRotateX->setText(QString::number(value));
  paint_model->onRotate(ui->scrollRotateX->value(), 0, 0);
}

void PaintViewer::on_boxRotateX_textChanged(const QString &text) {
  updateTextBox(text, ui->boxRotateX, ui->scrollRotateX);
}

void PaintViewer::on_scrollRotateY_valueChanged(int value) {
  ui->boxRotateY->setText(QString::number(value));
  paint_model->onRotate(0, ui->scrollRotateY->value(), 0);
}
void PaintViewer::on_boxRotateY_textChanged(const QString &text) {
  updateTextBox(text, ui->boxRotateY, ui->scrollRotateY);
}

void PaintViewer::on_scrollRotateZ_valueChanged(int value) {
  ui->boxRotateZ->setText(QString::number(value));
  paint_model->onRotate(0, 0, ui->scrollRotateZ->value());
}
void PaintViewer::on_boxRotateZ_textChanged(const QString &text) {
  updateTextBox(text, ui->boxRotateZ, ui->scrollRotateZ);
}

void PaintViewer::on_scrollScale_valueChanged(int value) {
  ui->boxScale->setText(QString::number(value));
  // paint_model->onScale(value, value, 0);
}
void PaintViewer::on_boxScale_textChanged(const QString &text) {
  updateTextBox(text, ui->boxScale, ui->scrollScale);
}

void PaintViewer::on_thicknessSelectFacets_valueChanged() {
  QToolTip::showText(QCursor::pos(),
                     QString::number(ui->thicknessSelectFacets->value()), this);
}

void PaintViewer::on_sizeSelectVerties_valueChanged() {
  QToolTip::showText(QCursor::pos(),
                     QString::number(ui->sizeSelectVerties->value()), this);
}

void PaintViewer::on_colorSelectFacets_pressed() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет ребер");

  if (color.isValid()) {
    // измение цвета для ребер
  }
}

void PaintViewer::on_colorSelectVertices_pressed() {
  QColor color =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет вершин");

  if (color.isValid()) {
    // измение цвета для вершин
  }
}

void PaintViewer::on_colorSelectBackground_pressed() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");

  if (color.isValid()) {
    // измение цвета для фона
  }
}

void PaintViewer::on_resetSettings_pressed() {
  on_scrollShiftX_valueChanged(0);
  on_scrollShiftY_valueChanged(0);
  on_scrollShiftZ_valueChanged(0);

  // on_scrollRotateX_valueChanged(0);
  // on_scrollRotateY_valueChanged(0);
  // on_scrollRotateZ_valueChanged(0);

  // on_scrollScale_valueChanged(0);
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
    QMessageBox::warning(this, tr("Warning"), tr("Could not save the file"));
  }
}

void PaintViewer::on_saveAsGif_pressed() {}