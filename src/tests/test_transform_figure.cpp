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
    return NormalizeParameters::getMinCoord(v);
  }
  static Vertex TestGetMaxCoord(const QVector<Vertex> &v) {
    return NormalizeParameters::getMaxCoord(v);
  }
  static Vertex TestGetCentralCoord(const Vertex minV, const Vertex maxV) {
    return NormalizeParameters::getCentralCoord(minV, maxV);
  }
  static void TestSetCentralVertex(QVector<Vertex> &v) {
    NormalizeParameters::setCentralVertex(v);
  }
  static void TestSetScaleVertex(QVector<Vertex> &v) {
    NormalizeParameters::setScaleVertex(v);
  }
};
}  // namespace s21

// Тест метода transform, который выполняет преобразование вершин
TEST_F(TransformFigureTest, Transform) {
  Figure figure(testFileName);

  auto originalVertex = figure.getVertices()[0];

  TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  EXPECT_NE(originalVertex.x(), figure.getVertices()[0].x());
  EXPECT_NE(originalVertex.y(), figure.getVertices()[0].y());
  EXPECT_NE(originalVertex.z(), figure.getVertices()[0].z());
}

// Тест метода transform, который не меняет количество вершин
TEST_F(TransformFigureTest, TransformDoesNotChangeVertexCount) {
  Figure figure(testFileName);

  int originalVertexCount = figure.getVertices().size();

  TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  ASSERT_EQ(figure.getVertices().size(), originalVertexCount);
}

// Тест, который проверяет, что преобразование не изменяет количество граней
TEST_F(TransformFigureTest, TransformDoesNotChangeFacetCount) {
  Figure figure(testFileName);

  int originalFacetCount = figure.getFacets().size();

  TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  ASSERT_EQ(figure.getFacets().size(), originalFacetCount);
}

// Проверяет, что метод getMinCoord находит минимальные координаты среди всех
// вершин.
TEST_F(TransformFigureTest, GetMinCoord) {
  Figure figure(testFileName);
  QVector<Vertex> vertices = figure.getVertices();

  Vertex minCoord = TestNormalizeParameters::TestGetMinCoord(vertices);

  EXPECT_NEAR(minCoord.x(), -1, EPS);
  EXPECT_NEAR(minCoord.y(), -1, EPS);
  EXPECT_NEAR(minCoord.z(), -1, EPS);
}

// Проверяет, что метод getMaxCoord находит максимальные координаты среди всех
// вершин.
TEST_F(TransformFigureTest, GetMaxCoord) {
  Figure figure(testFileName);

  QVector<Vertex> vertices = figure.getVertices();

  Vertex maxCoord = TestNormalizeParameters::TestGetMaxCoord(vertices);

  EXPECT_NEAR(maxCoord.x(), 1, EPS);
  EXPECT_NEAR(maxCoord.y(), 1, EPS);
  EXPECT_NEAR(maxCoord.z(), 1, EPS);
}

// Проверяет, что метод getCentralCoord правильно вычисляет центральную точку
// между минимальными и максимальными координатами.
TEST_F(TransformFigureTest, GetCentralCoord) {
  Figure figure(testFileName);

  QVector<Vertex> vertices = figure.getVertices();
  Vertex minCoord = TestNormalizeParameters::TestGetMinCoord(vertices);
  Vertex maxCoord = TestNormalizeParameters::TestGetMaxCoord(vertices);

  Vertex centralCoord =
      TestNormalizeParameters::TestGetCentralCoord(minCoord, maxCoord);

  EXPECT_NEAR(centralCoord.x(), 0, EPS);
  EXPECT_NEAR(centralCoord.y(), 0, EPS);
  EXPECT_NEAR(centralCoord.z(), 0, EPS);
}

// Проверяет, что метод setCentralVertex правильно перемещает все вершины
// относительно центральной точки.
TEST_F(TransformFigureTest, SetCentralVertex) {
  Figure figure(testFileName);

  QVector<Vertex> verticesBefore = figure.getVertices();

  Vertex minCoord = TestNormalizeParameters::TestGetMinCoord(verticesBefore);
  Vertex maxCoord = TestNormalizeParameters::TestGetMaxCoord(verticesBefore);
  TestNormalizeParameters::TestSetCentralVertex(verticesBefore);

  Vertex centralVertex =
      TestNormalizeParameters::TestGetCentralCoord(minCoord, maxCoord);

  EXPECT_EQ(centralVertex.x(), 0);
  EXPECT_EQ(centralVertex.y(), 0);
  EXPECT_EQ(centralVertex.z(), 0);
}

// Проверяет, что метод setScaleVertex корректно масштабирует вершины в диапазон
// от -1 до 1.
TEST_F(TransformFigureTest, SetScaleVertex) {
  Figure figure(testFileName);

  QVector<Vertex> verticesBefore = figure.getVertices();

  TestNormalizeParameters::TestSetScaleVertex(verticesBefore);

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
  Figure figure(testFileName);

  QVector<Vertex> verticesBefore = figure.getVertices();

  NormalizeParameters::setNormalVertex(verticesBefore);

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
  Figure figure(testFileName);

  QVector<Edge> originalFacets = figure.getFacets();

  ASSERT_FALSE(originalFacets.isEmpty());

  QVector<Edge> facetsWithDuplicates = originalFacets;
  facetsWithDuplicates.append(originalFacets[0]);
  facetsWithDuplicates.append(originalFacets[1]);

  int originalCount = facetsWithDuplicates.size();
  int uniqueCount =
      std::unordered_set<Edge, Edge::HashEdge>(facetsWithDuplicates.begin(),
                                               facetsWithDuplicates.end())
          .size();
  ASSERT_GT(originalCount, uniqueCount);

  NormalizeParameters::remDuplicateFaces(facetsWithDuplicates);

  EXPECT_EQ(facetsWithDuplicates.size(), uniqueCount);

  ASSERT_EQ(facetsWithDuplicates.size(), originalFacets.size());
  for (int i = 0; i < originalFacets.size(); ++i) {
    EXPECT_EQ(facetsWithDuplicates[i], originalFacets[i]);
  }
}

// Проверяет корректность масштабирования для нестандартных диапазонов координат
TEST_F(TransformFigureTest, ScaleWithNonStandardRange) {
  // QVector<Vertex> vertices = {
  //     {10.0, 20.0, -30.0}, {40.0, -50.0, 60.0}, {-70.0, 80.0, -90.0}};

  // TestNormalizeParameters::TestSetScaleVertex(vertices);

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
  QVector<Vertex> vertices = {
      {0.5, -0.5, 0.0}, {-0.8, 0.8, -0.2}, {0.0, 0.0, 0.0}};

  QVector<Vertex> expectedVertices = {{1.0f, -0.5384615, 0.2307692},
                                      {-1.0f, 1.4615385, -0.0769230},
                                      {0.23076927, 0.2307692, 0.2307692}};

  TestNormalizeParameters::TestSetScaleVertex(vertices);
  for (int i = 0; i < vertices.size(); ++i) {
    EXPECT_NEAR(vertices[i].x(), expectedVertices[i].x(), EPS);
    EXPECT_NEAR(vertices[i].y(), expectedVertices[i].y(), EPS);
    EXPECT_NEAR(vertices[i].z(), expectedVertices[i].z(), EPS);
  }
}

// Тест: Преобразование с нулевыми значениями
TEST_F(TransformFigureTest, TransformWithZeroValues) {
  Figure figure(testFileName);

  TransformMatrix transformMatrix;
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
