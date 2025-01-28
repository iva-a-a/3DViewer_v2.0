#include <gtest/gtest.h>
#include <QString>
#include <QVector>
#include <unordered_map>
#include <QTextStream>
#include "../model/figure.h"
#include <QDir>

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
  ASSERT_EQ(figure.getVertices().size(), 8);  // Проверка количества вершин
  ASSERT_EQ(figure.getFacets().size(), 18);  // Проверка количества граней
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

// Тест: Конструктор корректно обрабатывает невалидный файл
TEST_F(FigureTest, HandlesInvalidFileGracefully) {
  QString invalidFileName = "./models_3d/invalid.obj";

  EXPECT_NO_THROW({
      s21::Figure figure(invalidFileName);
      EXPECT_EQ(figure.getVertices().size(), 0u);  // Нет вершин
      EXPECT_EQ(figure.getFacets().size(), 0u);    // Нет граней
  });
}

// Тест: Нормализация вершин при создании объекта Figure
TEST_F(FigureTest, Normalization) {
  s21::Figure figure(testFileName);

  bool normalizationApplied = false;
  for (const auto &vertex : figure.getVertices()) {
    if (vertex.x() != 0.0 || vertex.y() != 0.0 || vertex.z() != 0.0) {
      normalizationApplied = true;
      break;
    }
  }

  ASSERT_TRUE(normalizationApplied);
}

// Тест: Нормализация вершин с использованием разных данных
TEST_F(FigureTest, NormalizationWithDifferentData) {
  QString anotherFileName = "./models_3d/another_cube.obj";
  s21::Figure figure(anotherFileName);

  bool normalizationApplied = false;
  for (const auto &vertex : figure.getVertices()) {
    if (vertex.x() != 0.0 || vertex.y() != 0.0 || vertex.z() != 0.0) {
      normalizationApplied = true;
      break;
    }
  }

  ASSERT_TRUE(normalizationApplied);
}

// Тест: Проверка методов getVertices и getFacets
TEST_F(FigureTest, GetVerticesAndFacets) {
  s21::Figure figure(testFileName);

  ASSERT_EQ(figure.getVertices().size(), 8);  // Проверка количества вершин
  ASSERT_EQ(figure.getFacets().size(), 18);  // Проверка количества граней

  const auto &vertices = figure.getVertices();
  float epsilon = 0.000001f;
  EXPECT_NEAR(vertices[0].x(), 1.0, epsilon);
  EXPECT_NEAR(vertices[0].y(), -1.0, epsilon);
  EXPECT_NEAR(vertices[0].z(), -1.0, epsilon);

  const auto &facets = figure.getFacets();
  EXPECT_NEAR(facets[0].getBeginPosition()->x(), 1.0, epsilon);
  EXPECT_NEAR(facets[0].getEndPosition()->x(), -1.0, epsilon);
}

// Тест: Обработка пустых данных
TEST_F(FigureTest, HandlesEmptyDataGracefully) {
    QString emptyFileName = "./models_3d/empty.obj";
    EXPECT_NO_THROW({
        s21::Figure figure(emptyFileName);
        EXPECT_EQ(figure.getVertices().size(), 0u);  
        EXPECT_EQ(figure.getFacets().size(), 0u);    
    });
}


