#pragma once

#include <QCloseEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QSlider>
#include <QTimer>
#include <QToolTip>

#include "paint_model.h"
#include "ui_paint.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}  // namespace Ui
QT_END_NAMESPACE

/**
 * @class PaintViewer
 * @brief Представляет окно для рисования.
 */
class PaintViewer : public QMainWindow {
  Q_OBJECT
 private:
  /** Указатель на объект Ui::MainWindow. */
  Ui::MainWindow *ui;
  /** Указатель на объект PaintModel. */
  PaintModel *paint_model;

 public:
  /**
   * @brief Конструктор класса PaintViewer.
   * @param parent Указатель на родительский объект.
   * @param c Указатель на объект Facade.
   */
  PaintViewer(QMainWindow *parent, Facade *c);
  /**
   * @brief Деструктор класса PaintViewer.
   */
  ~PaintViewer();

  /**
   * @brief Обработка события закрытия окна.
   * @param event Ссылка на событие закрытия.
   */
  void closeEvent(QCloseEvent *event) override;

 private slots:

  /**
   * @brief Обработка изменения значения ползунка сдвига по оси OX.
   * @param value Значение ползунка.
   */
  void on_scrollShiftX_valueChanged(int value);
  /**
   * @brief Обработка изменение текста в поле сдвига по оси OX.
   * @param text Текст поля.
   */
  void on_boxShiftX_textChanged(const QString &text);
  /**
   * @brief Обработка изменения значения ползунка сдвига по оси OY.
   * @param value Значение ползунка.
   */
  void on_scrollShiftY_valueChanged(int value);
  /**
   * @brief Обработка изменение текста в поле сдвига по оси OY.
   * @param text Текст поля.
   */
  void on_boxShiftY_textChanged(const QString &text);
  /**
   * @brief Обработка изменения значения ползунка сдвига по оси OZ.
   * @param value Значение ползунка.
   */
  void on_scrollShiftZ_valueChanged(int value);
  /**
   * @brief Обработка изменение текста в поле сдвига по оси OZ.
   * @param text Текст поля.
   */
  void on_boxShiftZ_textChanged(const QString &text);

  /**
   * @brief Обработка изменения значения ползунка поворота по оси OX.
   * @param value Значение ползунка.
   */
  void on_scrollRotateX_valueChanged(int value);
  /**
   * @brief Обработка изменения текста в поле поворота по оси OX.
   * @param text Текст поля.
   */
  void on_boxRotateX_textChanged(const QString &text);
  /**
   * @brief Обработка изменения значения ползунка поворота по оси OY.
   * @param value Значение ползунка.
   */
  void on_scrollRotateY_valueChanged(int value);
  /**
   * @brief Обработка изменения текста в поле поворота по оси OY.
   * @param text Текст поля.
   */
  void on_boxRotateY_textChanged(const QString &text);
  /**
   * @brief Обработка изменения значения ползунка поворота по оси OZ.
   * @param value Значение ползунка.
   */
  void on_scrollRotateZ_valueChanged(int value);
  /**
   * @brief Обработка изменения текста в поле поворота по оси OZ.
   * @param text Текст поля.
   */
  void on_boxRotateZ_textChanged(const QString &text);

  /**
   * @brief Обработка изменения значения ползунка масштабирования.
   * @param value Значение ползунка.
   */
  void on_scrollScale_valueChanged(int value);
  /**
   * @brief Обработка изменения текста в поле масштабирования.
   * @param text Текст поля.
   */
  void on_boxScale_textChanged(const QString &text);

  /**
   * @brief Обработка изменения значения толщины линий граней.
   */
  void on_thicknessSelectFacets_valueChanged();
  /**
   * @brief Обработка изменения типа линий граней.
   * @param index Индекс выбранного типа.
   */
  void on_typeSelectFacets_currentIndexChanged(int index);
  /**
   * @brief Обработка изменения цвета линий граней.
   */
  void on_colorSelectFacets_pressed();

  /**
   * @brief Обработка изменения значения размера вершин.
   */
  void on_sizeSelectVerties_valueChanged();
  /**
   * @brief Обработка изменения типа вершин.
   * @param index Индекс выбранного типа.
   */
  void on_typeSelectVertices_currentIndexChanged(int index);
  /**
   * @brief Обработка изменения цвета вершин.
   */
  void on_colorSelectVertices_pressed();

  /**
   * @brief Обработка изменения цвета фона.
   */
  void on_colorSelectBackground_pressed();

  /**
   * @brief Обработка изменения типа проекции.
   * @param index Индекс выбранного типа.
   */
  void on_typeProjection_currentIndexChanged(int index);

  /**
   * @brief Обработка нажатия кнопки выбора файла.
   */
  void on_chooseFile_pressed();

  /**
   * @brief Обработка нажатия кнопки сброса настроек.
   */
  void on_resetSettings_pressed();

  /**
   * @brief Обработка нажатия кнопки сохранения изображения в формате jpeg/bmp.
   */
  void on_saveAsBmpOrJpeg_pressed();
  /**
   * @brief Обработка нажатия кнопки сохранения изображения в формате gif
   * (анимированное изображение).
   */
  void on_saveAsGif_pressed();

 private:
  /**
   * @brief Обновление текстового поля и ползунка.
   * @param text Текст поля.
   * @param line Ссылка на текстовое поле.
   * @param scroll Ссылка на ползунок.
   */
  void updateTextBox(const QString &text, QLineEdit *line, QScrollBar *scroll);
  /**
   * @brief Инициализация текстовых полей.
   */
  void initialize_text_box();

  /**
   * @brief Установка текста в QTextBrowser.
   * @param text Ссылка на QTextBrowser.
   * @param size Число (количество).
   */
  void set_textToQTextBrowser(QTextBrowser *text, const size_t size);
  /**
   * @brief Установка имени файла в соответсвующее поле.
   * @param filename Имя файла.
   */
  void set_file_name(const QString &filename);
  /**
   * @brief Сброс настроек кнопок.
   */
  void reset_button();
  /**
   * @brief Установка начальных настроек из сохраненного файла.
   */
  void set_start_saved_settings();
  /**
   * @brief Получение имени файла из полного пути.
   * @param filePath Путь к файлу.
   * @return Имя файла.
   */
  QString get_filename(const QString &filePath);
  /**
   * @brief Включение или выключение кнопок.
   * @param enabled Флаг включения/выключения.
   */
  void set_onOrOff_buttons(bool enabled);

  /** Указатель на таймер для записи скринкаста. */
  QTimer *_screencastTimer;
  /** Счетчик кадров. */
  int _frameCounter;
  /** Папка для временных файлов для gif и для сохраненного gif изобажения. */
  QString _outputDir;
  /**
   * @brief Запись отдельного кадра для gif.
   */
  void recordFrame();
  /**
   * @brief Обновление таймера записи gif при нажатии на кнопку записи.
   */
  void updateCountdown();
};