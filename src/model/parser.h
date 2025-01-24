#pragma once

#include <QFile>
#include <QString>

#include "transform_figure.h"

namespace s21 {

/**
 * @class Parser
 * @brief Класс для парсинга и сохранения вершин и граней .obj файла.
 */
class Parser {
private:
  /**
   * @brief Конструктор класса Parser.
   */
  Parser() {}

  /**
   * @brief Деструктор класса Parser.
   */
  ~Parser() = default;

  /**
   * @brief Сохранение координат вершины из строки.
   * @param str Список строк
   * @param vertices Ссылка на список вершин.
   */
  static void saveCoordVertices(QStringList str, QVector<Vertex> &vertices);

  /**
   * @brief Сохранение ссылок на грани из строки.
   * @param str Список строк
   * @param facets Ссылка на список граней.
   * @param vertices Ссылка на список вершин.
   */
  static void saveRefFacets(QStringList str, QVector<Edge> &facets,
                            QVector<Vertex> &vertices);

public:
  /**
   * @brief Запись координат вершин и ссылокна грани из файла.
   * @param filename Имя файла с данными.
   * @param vertices Ссылка на список вершин.
   * @param facets Ссылка на список граней.
   */
  static void recordCoordFromFile(const QString &filename,
                                  QVector<Vertex> &vertices,
                                  QVector<Edge> &facets);
};

} // namespace s21
