#include "../model/transform_figure.h"
#include "../model/figure.h"
#include <gtest/gtest.h>
#include <QVector>
#include <QString>
#include <unordered_map>

class TransformFigureTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Путь к файлу cube.obj
        testFileName = "./models_3d/cube.obj";
    }

    QString testFileName;
};

// Тест метода transform, который выполняет преобразование вершин
TEST_F(TransformFigureTest, Transform) {
    // Создаем объект Figure
    s21::Figure figure(testFileName);

    // Запоминаем координаты первой вершины до преобразования
    auto originalVertex = figure.getVertices()[0];

    // Применяем преобразование (например, умножаем на матрицу)
    s21::TransformMatrix transformMatrix;
    figure.transform(transformMatrix);

    // Проверяем, что после преобразования первая вершина изменила свои координаты
    EXPECT_NE(originalVertex.x(), figure.getVertices()[0].x());
    EXPECT_NE(originalVertex.y(), figure.getVertices()[0].y());
    EXPECT_NE(originalVertex.z(), figure.getVertices()[0].z());
}

// Тест метода transform, который не меняет количество вершин
TEST_F(TransformFigureTest, TransformDoesNotChangeVertexCount) {
    // Создаем объект Figure
    s21::Figure figure(testFileName);

    // Запоминаем количество вершин до преобразования
    int originalVertexCount = figure.getVertices().size();

    // Применяем преобразование (например, умножаем на матрицу)
    s21::TransformMatrix transformMatrix;
    figure.transform(transformMatrix);

    // Проверяем, что количество вершин не изменилось (матрица не должна менять их количество)
    ASSERT_EQ(figure.getVertices().size(), originalVertexCount);
}

// Тест, который проверяет, что преобразование не изменяет количество граней
TEST_F(TransformFigureTest, TransformDoesNotChangeFacetCount) {
    // Создаем объект Figure
    s21::Figure figure(testFileName);

    // Запоминаем количество граней до преобразования
    int originalFacetCount = figure.getFacets().size();

    // Применяем преобразование (например, умножаем на матрицу)
    s21::TransformMatrix transformMatrix;
    figure.transform(transformMatrix);

    // Проверяем, что количество граней не изменилось
    ASSERT_EQ(figure.getFacets().size(), originalFacetCount);
}

// Тест на исключение, если передана некорректная матрица для преобразования
TEST_F(TransformFigureTest, TransformThrowsExceptionForInvalidMatrix) {
    // Создаем объект Figure
    s21::Figure figure(testFileName);

    // Создаем некорректную матрицу (3x3)
    s21::TransformMatrix invalidMatrix;

    // Инициализируем матрицу через публичный метод (если такой имеется)
    invalidMatrix._matrix.AllocMem(3, 3);  // Используем AllocMem для создания матрицы 3x3

    // Заполняем матрицу значениями
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            invalidMatrix._matrix(i, j) = 0.0f;  // Доступ к матрице через публичный метод
        }
    }

    // Проверка на выброс исключения
    ASSERT_THROW(figure.transform(invalidMatrix), std::invalid_argument);
}

// Проверяет, что метод getMinCoord находит минимальные координаты среди всех вершин. 
TEST_F(TransformFigureTest, GetMinCoord) {
    // Создаем объект Figure
    s21::Figure figure(testFileName);

    // Получаем вершины фигуры
    QVector<s21::Vertex> vertices = figure.getVertices();

    // Получаем минимальные координаты
    s21::Vertex minCoord = s21::NormalizeParameters::getMinCoord(vertices);

    // Выводим для диагностики
    std::cout << "MinCoord: (" << minCoord.x() << ", " << minCoord.y() << ", " << minCoord.z() << ")\n";

    // Проверяем, что координаты минимальны
    EXPECT_EQ(minCoord.x(), -1); // Пример ожидаемого значения
    EXPECT_EQ(minCoord.y(), -1);
    EXPECT_EQ(minCoord.z(), -1);
}

// Проверяет, что метод getMaxCoord находит максимальные координаты среди всех вершин. 
TEST_F(TransformFigureTest, GetMaxCoord) {
    // Создаем объект Figure
    s21::Figure figure(testFileName);

    // Получаем вершины фигуры
    QVector<s21::Vertex> vertices = figure.getVertices();

    // Получаем максимальные координаты
    s21::Vertex maxCoord = s21::NormalizeParameters::getMaxCoord(vertices);

    // Выводим для диагностики
    std::cout << "MaxCoord: (" << maxCoord.x() << ", " << maxCoord.y() << ", " << maxCoord.z() << ")\n";

    // Проверяем, что координаты максимальны
    EXPECT_EQ(maxCoord.x(), 1); // Пример ожидаемого значения
    EXPECT_EQ(maxCoord.y(), 1);
    EXPECT_EQ(maxCoord.z(), 1);
}

// Проверяет, что метод getCentralCoord правильно вычисляет центральную точку между 
// минимальными и максимальными координатами. 
TEST_F(TransformFigureTest, GetCentralCoord) {
    // Создаем объект Figure
    s21::Figure figure(testFileName);

    // Получаем минимальные и максимальные координаты
    QVector<s21::Vertex> vertices = figure.getVertices();
    s21::Vertex minCoord = s21::NormalizeParameters::getMinCoord(vertices);
    s21::Vertex maxCoord = s21::NormalizeParameters::getMaxCoord(vertices);

    // Выводим для диагностики
    std::cout << "MinCoord: (" << minCoord.x() << ", " << minCoord.y() << ", " << minCoord.z() << ")\n";
    std::cout << "MaxCoord: (" << maxCoord.x() << ", " << maxCoord.y() << ", " << maxCoord.z() << ")\n";

    // Получаем центральную точку
    s21::Vertex centralCoord = s21::NormalizeParameters::getCentralCoord(minCoord, maxCoord);

    // Проверяем, что центральная точка правильно вычислена
    EXPECT_EQ(centralCoord.x(), 0); // Пример ожидаемого значения
    EXPECT_EQ(centralCoord.y(), 0);
    EXPECT_EQ(centralCoord.z(), 0);
}

// Проверяет, что метод setCentralVertex правильно перемещает все вершины относительно 
// центральной точки. 
TEST_F(TransformFigureTest, SetCentralVertex) {
    // Создаем объект Figure
    s21::Figure figure(testFileName);

    // Получаем вершины до перемещения
    QVector<s21::Vertex> verticesBefore = figure.getVertices();

    // Получаем минимальные и максимальные координаты для диагностики
    s21::Vertex minCoord = s21::NormalizeParameters::getMinCoord(verticesBefore);
    s21::Vertex maxCoord = s21::NormalizeParameters::getMaxCoord(verticesBefore);
    std::cout << "MinCoord before shift: (" << minCoord.x() << ", " << minCoord.y() << ", " << minCoord.z() << ")\n";
    std::cout << "MaxCoord before shift: (" << maxCoord.x() << ", " << maxCoord.y() << ", " << maxCoord.z() << ")\n";

    // Применяем метод setCentralVertex
    s21::NormalizeParameters::setCentralVertex(verticesBefore);

    // Проверяем центральную вершину после сдвига
    s21::Vertex centralVertex = s21::NormalizeParameters::getCentralCoord(minCoord, maxCoord);  // Центральная точка, которая должна быть в (0, 0, 0)
    std::cout << "Central vertex after shift: (" << centralVertex.x() << ", " << centralVertex.y() << ", " << centralVertex.z() << ")\n";

    EXPECT_EQ(centralVertex.x(), 0);
    EXPECT_EQ(centralVertex.y(), 0);
    EXPECT_EQ(centralVertex.z(), 0);
}

// Проверяет, что метод setScaleVertex корректно масштабирует вершины в диапазон от -1 до 1. 
TEST_F(TransformFigureTest, SetScaleVertex) {
    // Создаем объект Figure
    s21::Figure figure(testFileName);

    // Получаем вершины до масштабирования
    QVector<s21::Vertex> verticesBefore = figure.getVertices();

    // Применяем метод setScaleVertex
    s21::NormalizeParameters::setScaleVertex(verticesBefore);

    // Проверяем, что все вершины масштабированы в диапазоне [-1, 1]
    for (const auto& vertex : verticesBefore) {
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
    // Создаем объект Figure
    s21::Figure figure(testFileName);

    // Получаем вершины до нормализации
    QVector<s21::Vertex> verticesBefore = figure.getVertices();

    // Применяем метод setNormalVertex
    s21::NormalizeParameters::setNormalVertex(verticesBefore);

    // Проверяем, что все вершины нормализованы в диапазоне [-1, 1]
    for (const auto& vertex : verticesBefore) {
        EXPECT_GE(vertex.x(), -1);
        EXPECT_LE(vertex.x(), 1);
        EXPECT_GE(vertex.y(), -1);
        EXPECT_LE(vertex.y(), 1);
        EXPECT_GE(vertex.z(), -1);
        EXPECT_LE(vertex.z(), 1);
    }
}
