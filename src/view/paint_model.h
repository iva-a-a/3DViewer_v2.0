#pragma once

#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <fstream>

#include "../controller/controller.h"

namespace s21 {

/**
 * @struct SettingVertex
 * @brief Настройки для отрисовки вершин.
 */
struct SettingVertex {
  /**
   * @enum Type
   * @brief Тип вершин.
   */
  enum class Type { Circle, Square, None };
  /** Текущий тип вершин. */
  Type type_vertex = Type::Circle;
  /** Текущий размер вершин. */
  int size_vertex = 1;
  /** Текущий цвет вершин. */
  QColor color_vertex = Qt::black;
};

/**
 * @struct SettingLines
 * @brief Настройки для отрисовки граней.
 */
struct SettingLines {
  /**
   * @enum Type
   * @brief Тип граней.
   */
  enum class Type { Solid, Dashed };
  /** Текущий тип граней. */
  Type type_lines = Type::Solid;
  /** Текущий толщина граней. */
  int line_thickness = 1;
  /** Текущий цвет граней. */
  QColor color_lines = Qt::black;
};

/**
 * @struct RenderSetting
 * @brief Настройки для отрисовки.
 */
struct RenderSetting {
  /** Текущий настройки вершин. */
  SettingVertex sett_v = {};
  /** Текущий настройки граней. */
  SettingLines sett_l = {};
  /** Текущий цвет фона. */
  QColor color_background = Qt::white;
};

/**
 * @class PaintModel
 * @brief Предназначен для отрисовки модели.
 */
class PaintModel : public QWidget {
  Q_OBJECT
 private:
  /** Указатель на контроллер. */
  Facade *controller;
  /** Настройки отрисовки. */
  RenderSetting s;

  /**
   * @brief Сброс настроек отрисовки.
   */
  void resetSetting();

  /**
   * @brief Отрисовка вершины.
   * @param painter Ссылка на объект QPainter.
   * @param point Ссылка на точку вершины.
   */
  void paintVertex(QPainter &painter, const QPointF &point) const;

  /**
   * @brief Запись координат точки с учетом проекции.
   * @param position Указатель на вершину.
   * @return Проекция точки.
   */
  QPointF projectPoint(const Vertex *position) const;

 public:
  /**
   * @brief Конструктор класса PaintModel.
   * @param parent Указатель на родительский объект.
   * @param c Указатель на объект Facade.
   */
  PaintModel(QWidget *parent, Facade *c)
      : QWidget(parent), controller(c), s({}) {}

  /**
   * @brief Деструктор класса PaintModel.
   */
  ~PaintModel() = default;

  /**
   * @brief Перемещение фигуры.
   * @param x Смещение по оси OX.
   * @param y Смещение по оси OY.
   * @param z Смещение по оси OZ.
   */
  void onMove(float x, float y, float z);

  /**
   * @brief Поворот фигуры.
   * @param x Угол поворота по оси OX.
   * @param y Угол поворота по оси OY.
   * @param z Угол поворота по оси OZ.
   */
  void onRotate(float x, float y, float z);

  /**
   * @brief Масштабирование фигуры.
   * @param x Масштаб по оси OX.
   * @param y Масштаб по оси OY.
   * @param z Масштаб по оси OZ.
   */
  void onScale(float x, float y, float z);

  /**
   * @brief Сброс параметров отрисовки и настроек.
   */
  void onReset();

  /**
   * @brief Получение количества вершин.
   * @return Количество вершин.
   */
  size_t onGetSizeVertices();

  /**
   * @brief Получение количества граней.
   * @return Количество граней.
   */
  size_t onGetSizeFacets();

  /**
   * @brief Загрузка модели.
   * @param filename Имя файла.
   */
  void onLoadModel(const QString &filename);

  /**
   * @brief Получение параметров контроллера.
   * @return Указатель на параметры контроллера.
   */
  Parameters *getParamController();
  /**
   * @brief Получение настроек отрисовки.
   * @return Указатель на настройки отрисовки.
   */
  RenderSetting *getSettingPaint();

 protected:
  /**
   * @brief Обработка события рисования.
   * @param event Ссылка на событие рисования.
   */
  void paintEvent(QPaintEvent *event) override;
};
}  // namespace s21
