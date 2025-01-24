#include <gtest/gtest.h>

#include <QString>
#include <QVector>

#include "../model/parser.h"

class ParserTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Путь к файлу cube.obj
    testFileName = "./models_3d/cube.obj";
    emptyFileName = "./models_3d/empty.obj";
    nonExistentFileName = "./models_3d/nonexistent.obj";
  }

  QString testFileName;
  QString emptyFileName;
  QString nonExistentFileName;
};

// Тест на чтение координат вершин и граней из файла
TEST_F(ParserTest, RecordCoordFromFile) {
  QVector<s21::Vertex> vertices;
  QVector<s21::Edge> facets;

  // Проверяем, что метод выполняется без исключений
  ASSERT_NO_THROW(
      s21::Parser::recordCoordFromFile(testFileName, vertices, facets));

  // Проверяем количество вершин
  ASSERT_EQ(vertices.size(), 8);  // В файле cube.obj должно быть 8 вершин

  // Проверяем координаты первой вершины
  EXPECT_FLOAT_EQ(vertices[0].x(), 1.0);
  EXPECT_FLOAT_EQ(vertices[0].y(), -1.0);
  EXPECT_FLOAT_EQ(vertices[0].z(), -1.0);

  // Проверяем количество граней
  ASSERT_EQ(facets.size(), 36);  // В файле cube.obj должно быть 36 граней
}

// Тест проверяет, как обрабатывается случай отсутствия файла.
TEST_F(ParserTest, FileNotFound) {
  QVector<s21::Vertex> vertices;
  QVector<s21::Edge> facets;

  // Проверяем, что выбрасывается std::runtime_error
  try {
    s21::Parser::recordCoordFromFile(nonExistentFileName, vertices, facets);
    FAIL() << "Expected std::runtime_error";
  } catch (const std::runtime_error &e) {
    EXPECT_STREQ(e.what(), "Cannot open file: ./models_3d/nonexistent.obj");
  } catch (...) {
    FAIL() << "Expected std::runtime_error, but caught a different exception";
  }
}

// Тест проверяет обработку пустого файла
TEST_F(ParserTest, EmptyFile) {
  QVector<s21::Vertex> vertices;
  QVector<s21::Edge> facets;

  // Создаем пустой файл
  QFile file(emptyFileName);
  if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    file.close();
  } else {
    FAIL() << "Could not create empty file for testing.";
  }

  // Проверяем, что метод выполняется без исключений, но данные остаются пустыми
  ASSERT_NO_THROW(
      s21::Parser::recordCoordFromFile(emptyFileName, vertices, facets));
  ASSERT_TRUE(vertices.isEmpty());
  ASSERT_TRUE(facets.isEmpty());
}
