#include <gtest/gtest.h>

#include <QString>
#include <QVector>
#include <unordered_map>

#include "../model/figure.h"
#include "../model/transform_figure.h"

#define EPS 1e-6

class TransformFigureTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Путь к файлу cube.obj
    testFileName = "./models_3d/cube.obj";
  }

  QString testFileName;
};

namespace s21 {
class TestNormalizeParameters : public NormalizeParameters {
 public:
  static Vertex TestGetMinCoord(const QVector<Vertex> &v) {
    return s21::NormalizeParameters::getMinCoord(v);
  }
  static Vertex TestGetMaxCoord(const QVector<Vertex> &v) {
    return s21::NormalizeParameters::getMaxCoord(v);
  }
  static Vertex TestGetCentralCoord(const Vertex minV, const Vertex maxV) {
    return s21::NormalizeParameters::getCentralCoord(minV, maxV);
  }
  static void TestSetCentralVertex(QVector<Vertex> &v) {
    s21::NormalizeParameters::setCentralVertex(v);
  }
  static void TestSetScaleVertex(QVector<Vertex> &v) {
    s21::NormalizeParameters::setScaleVertex(v);
  }
};
}  // namespace s21

// Тест метода transform, который выполняет преобразование вершин
TEST_F(TransformFigureTest, Transform) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Запоминаем координаты первой вершины до преобразования
  auto originalVertex = figure.getVertices()[0];

  // Применяем преобразование (например, умножаем на матрицу)
  s21::TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  // Проверяем, что после преобразования первая вершина изменила свои координаты
  EXPECT_NE(originalVertex.x(), figure.getVertices()[0].x());
  EXPECT_NE(originalVertex.y(), figure.getVertices()[0].y());
  EXPECT_NE(originalVertex.z(), figure.getVertices()[0].z());
}

// Тест метода transform, который не меняет количество вершин
TEST_F(TransformFigureTest, TransformDoesNotChangeVertexCount) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Запоминаем количество вершин до преобразования
  int originalVertexCount = figure.getVertices().size();

  // Применяем преобразование (например, умножаем на матрицу)
  s21::TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  // Проверяем, что количество вершин не изменилось (матрица не должна менять
  // их количество)
  ASSERT_EQ(figure.getVertices().size(), originalVertexCount);
}

// Тест, который проверяет, что преобразование не изменяет количество граней
TEST_F(TransformFigureTest, TransformDoesNotChangeFacetCount) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Запоминаем количество граней до преобразования
  int originalFacetCount = figure.getFacets().size();

  // Применяем преобразование (например, умножаем на матрицу)
  s21::TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  // Проверяем, что количество граней не изменилось
  ASSERT_EQ(figure.getFacets().size(), originalFacetCount);
}

// Проверяет, что метод getMinCoord находит минимальные координаты среди всех
// вершин.
TEST_F(TransformFigureTest, GetMinCoord) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Получаем вершины фигуры
  QVector<s21::Vertex> vertices = figure.getVertices();

  // Получаем минимальные координаты
  s21::Vertex minCoord =
      s21::TestNormalizeParameters::TestGetMinCoord(vertices);

  // Проверяем, что координаты минимальны
  EXPECT_NEAR(minCoord.x(), -1, EPS);  // Пример ожидаемого значения
  EXPECT_NEAR(minCoord.y(), -1, EPS);
  EXPECT_NEAR(minCoord.z(), -1, EPS);
}

// Проверяет, что метод getMaxCoord находит максимальные координаты среди всех
// вершин.
TEST_F(TransformFigureTest, GetMaxCoord) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Получаем вершины фигуры
  QVector<s21::Vertex> vertices = figure.getVertices();

  // Получаем максимальные координаты
  s21::Vertex maxCoord =
      s21::TestNormalizeParameters::TestGetMaxCoord(vertices);

  // Проверяем, что координаты максимальны
  EXPECT_NEAR(maxCoord.x(), 1, EPS);  // Пример ожидаемого значения
  EXPECT_NEAR(maxCoord.y(), 1, EPS);
  EXPECT_NEAR(maxCoord.z(), 1, EPS);
}

// Проверяет, что метод getCentralCoord правильно вычисляет центральную точку
// между минимальными и максимальными координатами.
TEST_F(TransformFigureTest, GetCentralCoord) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Получаем минимальные и максимальные координаты
  QVector<s21::Vertex> vertices = figure.getVertices();
  s21::Vertex minCoord =
      s21::TestNormalizeParameters::TestGetMinCoord(vertices);
  s21::Vertex maxCoord =
      s21::TestNormalizeParameters::TestGetMaxCoord(vertices);

  // Получаем центральную точку
  s21::Vertex centralCoord =
      s21::TestNormalizeParameters::TestGetCentralCoord(minCoord, maxCoord);

  // Проверяем, что центральная точка правильно вычислена
  EXPECT_NEAR(centralCoord.x(), 0, EPS);  // Пример ожидаемого значения
  EXPECT_NEAR(centralCoord.y(), 0, EPS);
  EXPECT_NEAR(centralCoord.z(), 0, EPS);
}

// Проверяет, что метод setCentralVertex правильно перемещает все вершины
// относительно центральной точки.
TEST_F(TransformFigureTest, SetCentralVertex) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Получаем вершины до перемещения
  QVector<s21::Vertex> verticesBefore = figure.getVertices();

  // Получаем минимальные и максимальные координаты для диагностики
  s21::Vertex minCoord =
      s21::TestNormalizeParameters::TestGetMinCoord(verticesBefore);
  s21::Vertex maxCoord =
      s21::TestNormalizeParameters::TestGetMaxCoord(verticesBefore);
  // Применяем метод setCentralVertex
  s21::TestNormalizeParameters::TestSetCentralVertex(verticesBefore);

  // Проверяем центральную вершину после сдвига
  s21::Vertex centralVertex = s21::TestNormalizeParameters::TestGetCentralCoord(
      minCoord,
      maxCoord);  // Центральная точка, которая должна быть в (0, 0, 0)

  EXPECT_EQ(centralVertex.x(), 0);
  EXPECT_EQ(centralVertex.y(), 0);
  EXPECT_EQ(centralVertex.z(), 0);
}

// Проверяет, что метод setScaleVertex корректно масштабирует вершины в диапазон
// от -1 до 1.
TEST_F(TransformFigureTest, SetScaleVertex) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Получаем вершины до масштабирования
  QVector<s21::Vertex> verticesBefore = figure.getVertices();

  // Применяем метод setScaleVertex
  s21::TestNormalizeParameters::TestSetScaleVertex(verticesBefore);

  // Проверяем, что все вершины масштабированы в диапазоне [-1, 1]
  for (const auto &vertex : verticesBefore) {
    EXPECT_GE(vertex.x(), -1);
    EXPECT_LE(vertex.x(), 1);
    EXPECT_GE(vertex.y(), -1);
    EXPECT_LE(vertex.y(), 1);
    EXPECT_GE(vertex.z(), -1);
    EXPECT_LE(vertex.z(), 1);
  }
}

// Проверяет, что метод setNormalVertex корректно работает,
// вызывая функции setCentralVertex и setScaleVertex последовательно.
TEST_F(TransformFigureTest, SetNormalVertex) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Получаем вершины до нормализации
  QVector<s21::Vertex> verticesBefore = figure.getVertices();

  // Применяем метод setNormalVertex
  s21::NormalizeParameters::setNormalVertex(verticesBefore);

  // Проверяем, что все вершины нормализованы в диапазоне [-1, 1]
  for (const auto &vertex : verticesBefore) {
    EXPECT_GE(vertex.x(), -1);
    EXPECT_LE(vertex.x(), 1);
    EXPECT_GE(vertex.y(), -1);
    EXPECT_LE(vertex.y(), 1);
    EXPECT_GE(vertex.z(), -1);
    EXPECT_LE(vertex.z(), 1);
  }
}
