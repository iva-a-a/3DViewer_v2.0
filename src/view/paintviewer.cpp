#include "paintviewer.h"

using namespace s21;

PaintViewer::PaintViewer(QMainWindow *parent) : QMainWindow(parent) {
  ui = new Ui::MainWindow;
  ui->setupUi(this);
  paint_model = new PaintModel(ui->field);
  paint_model->setGeometry(
      QRect(0, 0, ui->field->width() - 10, ui->field->height() - 10));
};

PaintViewer::~PaintViewer() {
  delete ui;
  delete paint_model;
};

void PaintViewer::setModel(ObjModel &m) { paint_model->setModel(m); }

void PaintViewer::updateTextBox(const QString &text, QLineEdit *line,
                                QScrollBar *scroll) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok) {
    scroll->setValue(value);
  }
  if (value > ui->scrollShiftX->maximum()) {
    line->setText(QString::number(scroll->maximum()));
  }
  if (value < ui->scrollShiftX->minimum()) {
    line->setText(QString::number(scroll->minimum()));
  }
}

void PaintViewer::on_scrollShiftX_valueChanged(int value) {
  ui->boxShiftX->setText(QString::number(value));
}

void PaintViewer::on_boxShiftX_textChanged(const QString &text) {
  updateTextBox(text, ui->boxShiftX, ui->scrollShiftX);
}

void PaintViewer::on_scrollShiftY_valueChanged(int value) {
  ui->boxShiftY->setText(QString::number(value));
}

void PaintViewer::on_boxShiftY_textChanged(const QString &text) {
  updateTextBox(text, ui->boxShiftY, ui->scrollShiftY);
}

void PaintViewer::on_scrollShiftZ_valueChanged(int value) {
  ui->boxShiftZ->setText(QString::number(value));
}

void PaintViewer::on_boxShiftZ_textChanged(const QString &text) {
  updateTextBox(text, ui->boxShiftZ, ui->scrollShiftZ);
}

void PaintViewer::on_scrollRotateX_valueChanged(int value) {
  ui->boxRotateX->setText(QString::number(value));
}

void PaintViewer::on_boxRotateX_textChanged(const QString &text) {
  updateTextBox(text, ui->boxRotateX, ui->scrollRotateX);
}

void PaintViewer::on_scrollRotateY_valueChanged(int value) {
  ui->boxRotateY->setText(QString::number(value));
}
void PaintViewer::on_boxRotateY_textChanged(const QString &text) {
  updateTextBox(text, ui->boxRotateY, ui->scrollRotateY);
}

void PaintViewer::on_scrollRotateZ_valueChanged(int value) {
  ui->boxRotateZ->setText(QString::number(value));
}
void PaintViewer::on_boxRotateZ_textChanged(const QString &text) {
  updateTextBox(text, ui->boxRotateZ, ui->scrollRotateZ);
}

void PaintViewer::on_scrollScale_valueChanged(int value) {
  ui->boxScale->setText(QString::number(value));
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
    //измение цвета для ребер
  }
}

void PaintViewer::on_colorSelectVertices_pressed() {
  QColor color =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет вершин");

  if (color.isValid()) {
    //измение цвета для вершин
  }
}

void PaintViewer::on_colorSelectBackground_pressed() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");

  if (color.isValid()) {
    //измение цвета для фона
  }
}

void PaintViewer::on_saveAsBmpOrJpeg_pressed() {
  QString format;
  QString fileName =
      QFileDialog::getSaveFileName(this, tr("Сохранить изображение"), "./",
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
  }
}

void PaintViewer::on_saveAsGif_pressed() {}