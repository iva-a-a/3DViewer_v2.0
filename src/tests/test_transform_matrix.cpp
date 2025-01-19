#include "../model/transform_matrix.h"
#include "../model/vertex_edge.h"
#include <fstream>
#include <gtest/gtest.h>
#include <cmath> // Для использования std::abs
#include <vector>

class TransformMatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Дополнительная настройка, если требуется
    }

    s21::TransformMatrix identityMatrix = s21::TransformMatrix(); // Единичная матрица
};

// Тест на умножение матриц
TEST_F(TransformMatrixTest, MultiplyMatrices) {
    s21::TransformMatrix m1;
    m1(0, 0) = 1; m1(0, 1) = 2; m1(0, 2) = 3; m1(0, 3) = 4;
    m1(1, 0) = 5; m1(1, 1) = 6; m1(1, 2) = 7; m1(1, 3) = 8;
    m1(2, 0) = 9; m1(2, 1) = 10; m1(2, 2) = 11; m1(2, 3) = 12;
    m1(3, 0) = 13; m1(3, 1) = 14; m1(3, 2) = 15; m1(3, 3) = 16;

    s21::TransformMatrix m2;
    m2(0, 0) = 16; m2(0, 1) = 15; m2(0, 2) = 14; m2(0, 3) = 13;
    m2(1, 0) = 12; m2(1, 1) = 11; m2(1, 2) = 10; m2(1, 3) = 9;
    m2(2, 0) = 8; m2(2, 1) = 7; m2(2, 2) = 6; m2(2, 3) = 5;
    m2(3, 0) = 4; m2(3, 1) = 3; m2(3, 2) = 2; m2(3, 3) = 1;

    s21::TransformMatrix result = m1 * m2;

    EXPECT_NEAR(result(0, 0), 80, 1e-6);
    EXPECT_NEAR(result(0, 1), 70, 1e-6);
    EXPECT_NEAR(result(0, 2), 60, 1e-6);
    EXPECT_NEAR(result(0, 3), 50, 1e-6);
}

// Тест на трансформацию точки
TEST_F(TransformMatrixTest, TransformPointTest) {
    // Создаем точку
    s21::Vertex v;
    v.setX(1.0);
    v.setY(2.0);
    v.setZ(3.0);
    
    // Создаем матрицу преобразования
    s21::TransformMatrix matrix;
    matrix.SetIdentityMatrix();  // Для простоты используем единичную матрицу
    
    // Преобразуем точку с помощью матрицы
    s21::Vertex result = matrix.transformPoint(v);
    
    // Проверяем, что преобразованная точка совпадает с исходной (единичная матрица не должна изменять точку)
    ASSERT_DOUBLE_EQ(result.x(), v.x());
    ASSERT_DOUBLE_EQ(result.y(), v.y());
    ASSERT_DOUBLE_EQ(result.z(), v.z());
}

// Тест на масштабирование
TEST_F(TransformMatrixTest, Scaling) {
    s21::TransformMatrix scaleMatrix;
    scaleMatrix(0, 0) = 2.0; // Масштабирование по x
    scaleMatrix(1, 1) = 3.0; // Масштабирование по y
    scaleMatrix(2, 2) = 4.0; // Масштабирование по z

    s21::Vertex point(1.0, 1.0, 1.0);
    s21::Vertex scaledPoint = scaleMatrix.transformPoint(point);

    EXPECT_NEAR(scaledPoint.x(), 2.0, 1e-6);
    EXPECT_NEAR(scaledPoint.y(), 3.0, 1e-6);
    EXPECT_NEAR(scaledPoint.z(), 4.0, 1e-6);
}

// Тест на доступ к элементам матрицы
TEST_F(TransformMatrixTest, AccessMatrixElements) {
    identityMatrix(0, 0) = 5.0;
    EXPECT_EQ(identityMatrix(0, 0), 5.0);
}

// Тест на проверку единичной матрицы
TEST_F(TransformMatrixTest, IdentityMatrix) {
    identityMatrix.SetIdentityMatrix();  // Устанавливаем единичную матрицу

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == j) {
                EXPECT_EQ(identityMatrix(i, j), 1.0);
            } else {
                EXPECT_EQ(identityMatrix(i, j), 0.0);
            }
        }
    }
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
