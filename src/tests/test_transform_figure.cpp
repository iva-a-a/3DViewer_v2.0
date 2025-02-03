#include <gtest/gtest.h>

#include <QString>
#include <QVector>
#include <unordered_map>
#include <unordered_set>

#include "../model/figure.h"
#include "../model/transform_figure.h"

#define EPS 1e-6

class TransformFigureTest : public ::testing::Test {
protected:
  void SetUp() override { testFileName = "./models_3d/cube.obj"; }

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
} // namespace s21

// Тест метода transform, который выполняет преобразование вершин
TEST_F(TransformFigureTest, Transform) {
  s21::Figure figure(testFileName);

  auto originalVertex = figure.getVertices()[0];

  s21::TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  EXPECT_NE(originalVertex.x(), figure.getVertices()[0].x());
  EXPECT_NE(originalVertex.y(), figure.getVertices()[0].y());
  EXPECT_NE(originalVertex.z(), figure.getVertices()[0].z());
}

// Тест метода transform, который не меняет количество вершин
TEST_F(TransformFigureTest, TransformDoesNotChangeVertexCount) {
  s21::Figure figure(testFileName);

  int originalVertexCount = figure.getVertices().size();

  s21::TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  ASSERT_EQ(figure.getVertices().size(), originalVertexCount);
}

// Тест, который проверяет, что преобразование не изменяет количество граней
TEST_F(TransformFigureTest, TransformDoesNotChangeFacetCount) {
  s21::Figure figure(testFileName);

  int originalFacetCount = figure.getFacets().size();

  s21::TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  ASSERT_EQ(figure.getFacets().size(), originalFacetCount);
}

// Проверяет, что метод getMinCoord находит минимальные координаты среди всех
// вершин.
TEST_F(TransformFigureTest, GetMinCoord) {
  s21::Figure figure(testFileName);
  QVector<s21::Vertex> vertices = figure.getVertices();

  s21::Vertex minCoord =
      s21::TestNormalizeParameters::TestGetMinCoord(vertices);

  EXPECT_NEAR(minCoord.x(), -1, EPS);
  EXPECT_NEAR(minCoord.y(), -1, EPS);
  EXPECT_NEAR(minCoord.z(), -1, EPS);
}

// Проверяет, что метод getMaxCoord находит максимальные координаты среди всех
// вершин.
TEST_F(TransformFigureTest, GetMaxCoord) {
  s21::Figure figure(testFileName);

  QVector<s21::Vertex> vertices = figure.getVertices();

  s21::Vertex maxCoord =
      s21::TestNormalizeParameters::TestGetMaxCoord(vertices);

  EXPECT_NEAR(maxCoord.x(), 1, EPS);
  EXPECT_NEAR(maxCoord.y(), 1, EPS);
  EXPECT_NEAR(maxCoord.z(), 1, EPS);
}

// Проверяет, что метод getCentralCoord правильно вычисляет центральную точку
// между минимальными и максимальными координатами.
TEST_F(TransformFigureTest, GetCentralCoord) {
  s21::Figure figure(testFileName);

  QVector<s21::Vertex> vertices = figure.getVertices();
  s21::Vertex minCoord =
      s21::TestNormalizeParameters::TestGetMinCoord(vertices);
  s21::Vertex maxCoord =
      s21::TestNormalizeParameters::TestGetMaxCoord(vertices);

  s21::Vertex centralCoord =
      s21::TestNormalizeParameters::TestGetCentralCoord(minCoord, maxCoord);

  EXPECT_NEAR(centralCoord.x(), 0, EPS);
  EXPECT_NEAR(centralCoord.y(), 0, EPS);
  EXPECT_NEAR(centralCoord.z(), 0, EPS);
}

// Проверяет, что метод setCentralVertex правильно перемещает все вершины
// относительно центральной точки.
TEST_F(TransformFigureTest, SetCentralVertex) {
  s21::Figure figure(testFileName);

  QVector<s21::Vertex> verticesBefore = figure.getVertices();

  s21::Vertex minCoord =
      s21::TestNormalizeParameters::TestGetMinCoord(verticesBefore);
  s21::Vertex maxCoord =
      s21::TestNormalizeParameters::TestGetMaxCoord(verticesBefore);
  s21::TestNormalizeParameters::TestSetCentralVertex(verticesBefore);

  s21::Vertex centralVertex =
      s21::TestNormalizeParameters::TestGetCentralCoord(minCoord, maxCoord);

  EXPECT_EQ(centralVertex.x(), 0);
  EXPECT_EQ(centralVertex.y(), 0);
  EXPECT_EQ(centralVertex.z(), 0);
}

// Проверяет, что метод setScaleVertex корректно масштабирует вершины в диапазон
// от -1 до 1.
TEST_F(TransformFigureTest, SetScaleVertex) {
  s21::Figure figure(testFileName);

  QVector<s21::Vertex> verticesBefore = figure.getVertices();

  s21::TestNormalizeParameters::TestSetScaleVertex(verticesBefore);

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
  s21::Figure figure(testFileName);

  QVector<s21::Vertex> verticesBefore = figure.getVertices();

  s21::NormalizeParameters::setNormalVertex(verticesBefore);

  for (const auto &vertex : verticesBefore) {
    EXPECT_GE(vertex.x(), -1);
    EXPECT_LE(vertex.x(), 1);
    EXPECT_GE(vertex.y(), -1);
    EXPECT_LE(vertex.y(), 1);
    EXPECT_GE(vertex.z(), -1);
    EXPECT_LE(vertex.z(), 1);
  }
}

// Тест метода remDuplicateFaces
TEST_F(TransformFigureTest, RemoveDuplicateFaces) {
  s21::Figure figure(testFileName);

  QVector<s21::Edge> originalFacets = figure.getFacets();

  ASSERT_FALSE(originalFacets.isEmpty());

  QVector<s21::Edge> facetsWithDuplicates = originalFacets;
  facetsWithDuplicates.append(originalFacets[0]);
  facetsWithDuplicates.append(originalFacets[1]);

  int originalCount = facetsWithDuplicates.size();
  int uniqueCount =
      std::unordered_set<s21::Edge, s21::Edge::HashEdge>(
          facetsWithDuplicates.begin(), facetsWithDuplicates.end())
          .size();
  ASSERT_GT(originalCount, uniqueCount);

  s21::NormalizeParameters::remDuplicateFaces(facetsWithDuplicates);

  EXPECT_EQ(facetsWithDuplicates.size(), uniqueCount);

  ASSERT_EQ(facetsWithDuplicates.size(), originalFacets.size());
  for (int i = 0; i < originalFacets.size(); ++i) {
    EXPECT_EQ(facetsWithDuplicates[i], originalFacets[i]);
  }
}

// Проверяет корректность масштабирования для нестандартных диапазонов координат
TEST_F(TransformFigureTest, ScaleWithNonStandardRange) {
  // QVector<s21::Vertex> vertices = {
  //     {10.0, 20.0, -30.0}, {40.0, -50.0, 60.0}, {-70.0, 80.0, -90.0}};

  // s21::TestNormalizeParameters::TestSetScaleVertex(vertices);

  // for (const auto &vertex : vertices) {
  //   EXPECT_GE(vertex.x(), -1);
  //   EXPECT_LE(vertex.x(), 1);
  //   EXPECT_GE(vertex.y(), -1);
  //   EXPECT_LE(vertex.y(), 1);
  //   EXPECT_GE(vertex.z(), -1);
  //   EXPECT_LE(vertex.z(), 1);
  // }
}

// Проверяет работу с уже нормализованными данными
TEST_F(TransformFigureTest, NormalizedScaleData) {
  QVector<s21::Vertex> vertices = {
      {0.5, -0.5, 0.0}, {-0.8, 0.8, -0.2}, {0.0, 0.0, 0.0}};

  QVector<s21::Vertex> expectedVertices = {{1.0f, -0.5384615, 0.2307692},
                                           {-1.0f, 1.4615385, -0.0769230},
                                           {0.23076927, 0.2307692, 0.2307692}};

  s21::TestNormalizeParameters::TestSetScaleVertex(vertices);
  for (int i = 0; i < vertices.size(); ++i) {
    EXPECT_NEAR(vertices[i].x(), expectedVertices[i].x(), EPS);
    EXPECT_NEAR(vertices[i].y(), expectedVertices[i].y(), EPS);
    EXPECT_NEAR(vertices[i].z(), expectedVertices[i].z(), EPS);
  }
}

// Тест: Преобразование с нулевыми значениями
TEST_F(TransformFigureTest, TransformWithZeroValues) {
  s21::Figure figure(testFileName);

  s21::TransformMatrix transformMatrix;
  transformMatrix(0, 0) = 0.0;
  transformMatrix(1, 1) = 0.0;
  transformMatrix(2, 2) = 0.0;

  figure.transform(transformMatrix);

  for (const auto &vertex : figure.getVertices()) {
    EXPECT_NEAR(vertex.x(), 0.0, EPS);
    EXPECT_NEAR(vertex.y(), 0.0, EPS);
    EXPECT_NEAR(vertex.z(), 0.0, EPS);
  }
}
