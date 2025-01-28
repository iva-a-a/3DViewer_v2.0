#include <gtest/gtest.h>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>

#include "../model/parser.h"

class ParserTest : public ::testing::Test {
 protected:
  void SetUp() override {
    validFileName = "./models_3d/cube.obj";
    emptyFileName = "./models_3d/empty.obj";
    nonExistentFileName = "./models_3d/nonexistent.obj";
    invalidFormatFileName = "./models_3d/invalid_format.obj";
    unrecognizedLinesFileName = "./models_3d/unrecognized_lines.obj";
  }

  QString validFileName;
  QString emptyFileName;
  QString nonExistentFileName;
  QString invalidFormatFileName;
  QString unrecognizedLinesFileName;
};

// Тест на чтение координат вершин и граней из файла
TEST_F(ParserTest, RecordCoordFromFile) {
  QVector<s21::Vertex> vertices;
  QVector<s21::Edge> facets;

  ASSERT_NO_THROW(
      s21::Parser::recordCoordFromFile(validFileName, vertices, facets));

  ASSERT_EQ(vertices.size(), 8); 
  EXPECT_FLOAT_EQ(vertices[0].x(), 1.0);  
  EXPECT_FLOAT_EQ(vertices[0].y(), -1.0);
  EXPECT_FLOAT_EQ(vertices[0].z(), -1.0);

  ASSERT_EQ(facets.size(), 36);  
}

// Тест проверяет обработку отсутствующего файла
TEST_F(ParserTest, FileNotFound) {
  QVector<s21::Vertex> vertices;
  QVector<s21::Edge> facets;

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

  QFile file(emptyFileName);
  if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    file.close();
  } else {
    FAIL() << "Could not create empty file for testing.";
  }

  ASSERT_NO_THROW(
      s21::Parser::recordCoordFromFile(emptyFileName, vertices, facets));
  ASSERT_TRUE(vertices.isEmpty());
  ASSERT_TRUE(facets.isEmpty());
}

// Тест проверяет обработку файла с нераспознанными строками
TEST_F(ParserTest, UnrecognizedLinesInFile) {
  QVector<s21::Vertex> vertices;
  QVector<s21::Edge> facets;

  QFile file(unrecognizedLinesFileName);
  if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    QTextStream out(&file);
    out << "v 1.0 1.0 1.0\n";  
    out << "v -1.0 -1.0 -1.0\n";  
    out << "This is an unrecognized line\n"; 
    out << "v 0.0 0.0 0.0\n"; 
    file.close();
  } else {
    FAIL() << "Could not create unrecognized lines file for testing.";
  }

  ASSERT_NO_THROW(
      s21::Parser::recordCoordFromFile(unrecognizedLinesFileName, vertices, facets));

  ASSERT_EQ(vertices.size(), 3);
  EXPECT_FLOAT_EQ(vertices[0].x(), 1.0);
  EXPECT_FLOAT_EQ(vertices[0].y(), 1.0);
  EXPECT_FLOAT_EQ(vertices[0].z(), 1.0);

  EXPECT_FLOAT_EQ(vertices[1].x(), -1.0);
  EXPECT_FLOAT_EQ(vertices[1].y(), -1.0);
  EXPECT_FLOAT_EQ(vertices[1].z(), -1.0);

  EXPECT_FLOAT_EQ(vertices[2].x(), 0.0);
  EXPECT_FLOAT_EQ(vertices[2].y(), 0.0);
  EXPECT_FLOAT_EQ(vertices[2].z(), 0.0);

  ASSERT_TRUE(facets.isEmpty());
}

// Тест: Обработка файла с некорректными данными
TEST_F(ParserTest, InvalidDataInFile) {
    QVector<s21::Vertex> vertices;
    QVector<s21::Edge> facets;

    QString invalidDataFileName = "./models_3d/invalid_data.obj";
    QFile file(invalidDataFileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        out << "v 1.0 1.0 1.0\n";  
        out << "v -1.0 -1.0 -1.0\n";  
        out << "f 1 2 3\n";  // Некорректные индексы граней
        file.close();
    } else {
        FAIL() << "Could not create invalid data file for testing.";
    }

    ASSERT_NO_THROW(
        s21::Parser::recordCoordFromFile(invalidDataFileName, vertices, facets));

    ASSERT_EQ(vertices.size(), 2);
    EXPECT_FLOAT_EQ(vertices[0].x(), 1.0);
    EXPECT_FLOAT_EQ(vertices[0].y(), 1.0);
    EXPECT_FLOAT_EQ(vertices[0].z(), 1.0);

    EXPECT_FLOAT_EQ(vertices[1].x(), -1.0);
    EXPECT_FLOAT_EQ(vertices[1].y(), -1.0);
    EXPECT_FLOAT_EQ(vertices[1].z(), -1.0);

    ASSERT_TRUE(facets.isEmpty());
}

// Тест: Обработка файла с некорректными значениями вершин
TEST_F(ParserTest, InvalidVertexDataInFile) {
    QVector<s21::Vertex> vertices;
    QVector<s21::Edge> facets;

    QString invalidVertexFileName = "./models_3d/invalid_vertex.obj";
    QFile file(invalidVertexFileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        out << "v 1.0 abc 1.0\n";  // Некорректное значение
        file.close();
    } else {
        FAIL() << "Could not create invalid vertex file for testing.";
    }

    ASSERT_NO_THROW(
        s21::Parser::recordCoordFromFile(invalidVertexFileName, vertices, facets));
    ASSERT_TRUE(vertices.isEmpty());  // Ожидаем, что вершины не будут загружены
}