#include <gtest/gtest.h>

#include <cmath>
#include <fstream>
#include <vector>

#include "../model/transform_matrix.h"
#include "../model/vertex_edge.h"

class TransformMatrixTest : public ::testing::Test {
 protected:
  s21::TransformMatrix identityMatrix = s21::TransformMatrix();
};

// Тест на умножение матриц
TEST_F(TransformMatrixTest, MultiplyMatrices) {
  s21::TransformMatrix m1;
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(0, 3) = 4;
  m1(1, 0) = 5;
  m1(1, 1) = 6;
  m1(1, 2) = 7;
  m1(1, 3) = 8;
  m1(2, 0) = 9;
  m1(2, 1) = 10;
  m1(2, 2) = 11;
  m1(2, 3) = 12;
  m1(3, 0) = 13;
  m1(3, 1) = 14;
  m1(3, 2) = 15;
  m1(3, 3) = 16;

  s21::TransformMatrix m2;
  m2(0, 0) = 16;
  m2(0, 1) = 15;
  m2(0, 2) = 14;
  m2(0, 3) = 13;
  m2(1, 0) = 12;
  m2(1, 1) = 11;
  m2(1, 2) = 10;
  m2(1, 3) = 9;
  m2(2, 0) = 8;
  m2(2, 1) = 7;
  m2(2, 2) = 6;
  m2(2, 3) = 5;
  m2(3, 0) = 4;
  m2(3, 1) = 3;
  m2(3, 2) = 2;
  m2(3, 3) = 1;

  s21::TransformMatrix result = m1 * m2;

  EXPECT_NEAR(result(0, 0), 80, 1e-6);
  EXPECT_NEAR(result(0, 1), 70, 1e-6);
  EXPECT_NEAR(result(0, 2), 60, 1e-6);
  EXPECT_NEAR(result(0, 3), 50, 1e-6);
}

// Тест на масштабирование
TEST_F(TransformMatrixTest, Scaling) {
  s21::TransformMatrix scaleMatrix;
  scaleMatrix(0, 0) = 2.0;
  scaleMatrix(1, 1) = 3.0;
  scaleMatrix(2, 2) = 4.0;

  s21::Vertex point(1.0, 1.0, 1.0);
  scaleMatrix.transformPoint(point);

  EXPECT_NEAR(point.x(), 2.0, 1e-6);
  EXPECT_NEAR(point.y(), 3.0, 1e-6);
  EXPECT_NEAR(point.z(), 4.0, 1e-6);
}

// Тест на доступ к элементам матрицы
TEST_F(TransformMatrixTest, AccessMatrixElements) {
  identityMatrix(0, 0) = 5.0;
  EXPECT_EQ(identityMatrix(0, 0), 5.0);
}

// Тест на корректность инверсии
TEST_F(TransformMatrixTest, InverseMatrix) {
  s21::TransformMatrix invertibleMatrix;
  invertibleMatrix(0, 0) = 1;
  invertibleMatrix(1, 1) = 2;
  invertibleMatrix(2, 2) = 3;
  invertibleMatrix(3, 3) = 1;

  invertibleMatrix.InverseTransformMatrix();

  EXPECT_NEAR(invertibleMatrix(0, 0), 1.0, 1e-6);
  EXPECT_NEAR(invertibleMatrix(1, 1), 0.5, 1e-6);
  EXPECT_NEAR(invertibleMatrix(2, 2), 0.333333, 1e-6);
}

// Тест: Преобразование с нулевыми значениями
TEST_F(TransformMatrixTest, TransformWithZeroValues) {
  s21::TransformMatrix zeroMatrix;
  zeroMatrix(0, 0) = 0.0;
  zeroMatrix(1, 1) = 0.0;
  zeroMatrix(2, 2) = 0.0;

  s21::Vertex point(1.0, 1.0, 1.0);
  zeroMatrix.transformPoint(point);

  EXPECT_NEAR(point.x(), 0.0, 1e-6);
  EXPECT_NEAR(point.y(), 0.0, 1e-6);
  EXPECT_NEAR(point.z(), 0.0, 1e-6);
}