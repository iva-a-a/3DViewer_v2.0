#include "../model/transform_matrix_builder.h"
#include <gtest/gtest.h>
#include <QVector>
#include <QString>

class TransformMatrixBuilderTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Путь к файлу cube.obj
        testFileName = "./models_3d/cube.obj";
    }

    QString testFileName;
};

// Тест на создание матрицы вращения вокруг оси Z
TEST_F(TransformMatrixBuilderTest, CreateRotateMatrix) {
    // Угол вращения
    float a = 0.0f, b = 0.0f, c = 3.14159265359f;  // Поворот на 180 градусов вокруг оси Z

    s21::TransformMatrix result = s21::TransformMatrixBuilder::createRotateMatrix(a, b, c);

    // Проверяем значения в матрице
    EXPECT_FLOAT_EQ(result(0, 0), -1.0f);  // Элемент на позиции (0, 0) должен быть -1 для поворота на 180 градусов
    EXPECT_FLOAT_EQ(result(1, 1), -1.0f);  // Элемент на позиции (1, 1) должен быть -1 для поворота на 180 градусов
    EXPECT_FLOAT_EQ(result(2, 2), 1.0f);   // Элемент на позиции (2, 2) должен быть 1
}

// Тест на создание матрицы перемещения
TEST_F(TransformMatrixBuilderTest, CreateMoveMatrix) {
    // Перемещение на (1, 2, 3)
    float a = 1.0f, b = 2.0f, c = 3.0f;

    s21::TransformMatrix result = s21::TransformMatrixBuilder::createMoveMatrix(a, b, c);

    // Проверяем значения в матрице
    EXPECT_FLOAT_EQ(result(0, 3), 1.0f);  // Элемент на позиции (0, 3) должен быть 1
    EXPECT_FLOAT_EQ(result(1, 3), 2.0f);  // Элемент на позиции (1, 3) должен быть 2
    EXPECT_FLOAT_EQ(result(2, 3), 3.0f);  // Элемент на позиции (2, 3) должен быть 3
}

// Тест на создание матрицы масштабирования
TEST_F(TransformMatrixBuilderTest, CreateScaleMatrix) {
    // Масштабирование на (2, 3, 4)
    float a = 2.0f, b = 3.0f, c = 4.0f;

    s21::TransformMatrix result = s21::TransformMatrixBuilder::createScaleMatrix(a, b, c);

    // Проверяем значения в матрице
    EXPECT_FLOAT_EQ(result(0, 0), 2.0f);  // Элемент на позиции (0, 0) должен быть 2
    EXPECT_FLOAT_EQ(result(1, 1), 3.0f);  // Элемент на позиции (1, 1) должен быть 3
    EXPECT_FLOAT_EQ(result(2, 2), 4.0f);  // Элемент на позиции (2, 2) должен быть 4
}
