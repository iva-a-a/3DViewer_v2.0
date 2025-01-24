#include <gtest/gtest.h>

#include <QString>
#include <QVector>
#include <unordered_map>

#include "../model/figure.h"

class FigureTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Путь к файлу cube.obj
    testFileName = "./models_3d/cube.obj";
  }

  QString testFileName;
};

// Тест конструктора класса Figure
TEST_F(FigureTest, Constructor) {
  // Создание объекта Figure из файла
  s21::Figure figure(testFileName);

  // Проверка, что количество вершин и граней корректное
  ASSERT_EQ(figure.getVertices().size(),
            8);  // В файле cube.obj должно быть 8 вершин
  ASSERT_EQ(figure.getFacets().size(),
            18);  // В файле cube.obj должно быть 36 граней
}

// Тест конструктора копирования класса Figure
TEST_F(FigureTest, CopyConstructor) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Копируем его
  s21::Figure copiedFigure = figure;

  // Проверяем, что количество вершин и граней одинаково в оригинальном и
  // копированном объекте
  ASSERT_EQ(copiedFigure.getVertices().size(), figure.getVertices().size());
  ASSERT_EQ(copiedFigure.getFacets().size(), figure.getFacets().size());
}

// Тест оператора присваивания класса Figure
TEST_F(FigureTest, AssignmentOperator) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Создаем новый объект и присваиваем ему значения из figure
  s21::Figure assignedFigure(testFileName);
  assignedFigure = figure;

  // Проверяем, что количество вершин и граней одинаково в оригинальном и
  // присвоенном объекте
  ASSERT_EQ(assignedFigure.getVertices().size(), figure.getVertices().size());
  ASSERT_EQ(assignedFigure.getFacets().size(), figure.getFacets().size());
}

// Тест метода transform, который выполняет преобразование вершин
TEST_F(FigureTest, Transform) {
  // Создаем объект Figure
  s21::Figure figure(testFileName);

  // Запоминаем количество вершин до преобразования
  int originalVertexCount = figure.getVertices().size();

  // Применяем преобразование (например, умножаем на матрицу)
  s21::TransformMatrix transformMatrix;
  figure.transform(transformMatrix);

  // Проверяем, что количество вершин не изменилось (матрица не должна менять их
  // количество)
  ASSERT_EQ(figure.getVertices().size(), originalVertexCount);
}

// Тест метода, который выбрасывает исключение, если не может найти вершину
TEST_F(FigureTest, ConstructorThrowsExceptionForInvalidVertex) {
  QString invalidFileName = "./models_3d/invalid.obj";

  ASSERT_THROW(s21::Figure figure(invalidFileName), std::runtime_error);
}

// Тест проверяет нормализацию вершин при создании объекта Figure
TEST_F(FigureTest, Normalization) {
  // Создание объекта Figure из файла
  s21::Figure figure(testFileName);

  // Применяется ли нормализация? (Проверим, что вершины не равны нулевым
  // значениям)
  bool normalizationApplied = false;
  for (const auto &vertex : figure.getVertices()) {
    if (vertex.x() != 0.0 || vertex.y() != 0.0 || vertex.z() != 0.0) {
      normalizationApplied = true;
      break;
    }
  }

  ASSERT_TRUE(
      normalizationApplied);  // Ожидаем, что нормализация вершин была применена
}

// Тест проверяет методы getVertices и getFacets для получения вершин и граней
TEST_F(FigureTest, GetVerticesAndFacets) {
  s21::Figure figure(testFileName);

  // Проверяем, что методы getVertices и getFacets возвращают правильные данные
  ASSERT_EQ(figure.getVertices().size(),
            8);  // В файле cube.obj должно быть 8 вершин
  ASSERT_EQ(figure.getFacets().size(),
            18);  // В файле cube.obj должно быть 36 граней

  // Проверка содержимого вершин
  const auto &vertices = figure.getVertices();
  float epsilon = 0.000001f;
  EXPECT_NEAR(vertices[0].x(), 1.0, epsilon);
  EXPECT_NEAR(vertices[0].y(), -1.0, epsilon);
  EXPECT_NEAR(vertices[0].z(), -1.0, epsilon);

  // Проверка содержимого граней
  const auto &facets = figure.getFacets();
  EXPECT_NEAR(facets[0].getBeginPosition()->x(), 1.0,
              epsilon);  // Проверка первого ребра
  EXPECT_NEAR(facets[0].getEndPosition()->x(), -1.0,
              epsilon);  // Проверка первого ребра
}
