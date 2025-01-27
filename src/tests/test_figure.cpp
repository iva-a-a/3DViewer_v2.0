#include <gtest/gtest.h>

#include <QString>
#include <QVector>
#include <unordered_map>

#include "../model/figure.h"

class FigureTest : public ::testing::Test {
 protected:
  void SetUp() override {
    testFileName = "./models_3d/cube.obj";
  }

  QString testFileName;
};

// Тест конструктора класса Figure
TEST_F(FigureTest, Constructor) {
  s21::Figure figure(testFileName);
  ASSERT_EQ(figure.getVertices().size(),
            8);  
  ASSERT_EQ(figure.getFacets().size(),
            18);  
}

// Тест конструктора копирования класса Figure
TEST_F(FigureTest, CopyConstructor) {
  s21::Figure figure(testFileName);
  s21::Figure copiedFigure = figure;
  ASSERT_EQ(copiedFigure.getVertices().size(), figure.getVertices().size());
  ASSERT_EQ(copiedFigure.getFacets().size(), figure.getFacets().size());
}

// Тест оператора присваивания класса Figure
TEST_F(FigureTest, AssignmentOperator) {
  s21::Figure figure(testFileName);
  s21::Figure assignedFigure(testFileName);
  assignedFigure = figure;

  ASSERT_EQ(assignedFigure.getVertices().size(), figure.getVertices().size());
  ASSERT_EQ(assignedFigure.getFacets().size(), figure.getFacets().size());
}

// Тест метода transform, который выполняет преобразование вершин
TEST_F(FigureTest, Transform) {
  s21::Figure figure(testFileName);
  int originalVertexCount = figure.getVertices().size();

  s21::TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  ASSERT_EQ(figure.getVertices().size(), originalVertexCount);
}

// Тест метода, который выбрасывает исключение, если не может найти вершину
TEST_F(FigureTest, ConstructorThrowsExceptionForInvalidVertex) {
  QString invalidFileName = "./models_3d/invalid.obj";

  ASSERT_THROW(s21::Figure figure(invalidFileName), std::runtime_error);
}

// Тест проверяет нормализацию вершин при создании объекта Figure
TEST_F(FigureTest, Normalization) {
  s21::Figure figure(testFileName);

  bool normalizationApplied = false;
  for (const auto &vertex : figure.getVertices()) {
    if (vertex.x() != 0.0 || vertex.y() != 0.0 || vertex.z() != 0.0) {
      normalizationApplied = true;
      break;
    }
  }

  ASSERT_TRUE(
      normalizationApplied);  
}

// Тест проверяет методы getVertices и getFacets для получения вершин и граней
TEST_F(FigureTest, GetVerticesAndFacets) {
  s21::Figure figure(testFileName);

  ASSERT_EQ(figure.getVertices().size(),
            8);  
  ASSERT_EQ(figure.getFacets().size(),
            18); 

  const auto &vertices = figure.getVertices();
  float epsilon = 0.000001f;
  EXPECT_NEAR(vertices[0].x(), 1.0, epsilon);
  EXPECT_NEAR(vertices[0].y(), -1.0, epsilon);
  EXPECT_NEAR(vertices[0].z(), -1.0, epsilon);

  const auto &facets = figure.getFacets();
  EXPECT_NEAR(facets[0].getBeginPosition()->x(), 1.0,
              epsilon);  
  EXPECT_NEAR(facets[0].getEndPosition()->x(), -1.0,
              epsilon);  
}
