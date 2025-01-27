#include <gtest/gtest.h>
#include "../controller/controller.h"

const QString testFileName = "./models_3d/cube.obj";

// Тест: Инициализация параметров
TEST(FacadeTest, ResetParamTest) {
    s21::Facade facade;
    facade.resetParam();
    s21::Parameters *params = facade.getParam();

    EXPECT_FLOAT_EQ(params->scale, 1.0f);
    EXPECT_FLOAT_EQ(params->shift_x, 0.0f);
    EXPECT_FLOAT_EQ(params->shift_y, 0.0f);
    EXPECT_FLOAT_EQ(params->shift_z, 0.0f);
    EXPECT_FLOAT_EQ(params->rotate_x, 0.0f);
    EXPECT_FLOAT_EQ(params->rotate_y, 0.0f);
    EXPECT_FLOAT_EQ(params->rotate_z, 0.0f);
    EXPECT_EQ(params->type_projection, s21::ProjectionType::Parallel);
}

// Тест: Загрузка файла
TEST(FacadeTest, LoadFileTest) {
    s21::Facade facade;

    ASSERT_NO_THROW(facade.loadFile(testFileName));

    EXPECT_EQ(facade.getParam()->filename, testFileName);
    EXPECT_GT(facade.getSizeVertices(), 0u);
    EXPECT_GT(facade.getSizeFacets(), 0u);
}

// Тест: Перемещение фигуры
TEST(FacadeTest, MoveFigureTest) {
    s21::Facade facade;
    facade.resetParam();

    float move_x = 10.0f, move_y = 20.0f, move_z = 30.0f;
    facade.moveFigure(move_x, move_y, move_z);

    s21::Parameters *params = facade.getParam();
    EXPECT_FLOAT_EQ(params->shift_x, move_x);
    EXPECT_FLOAT_EQ(params->shift_y, move_y);
    EXPECT_FLOAT_EQ(params->shift_z, move_z);
}

// Тест: Вращение фигуры
TEST(FacadeTest, RotateFigureTest) {
    s21::Facade facade;
    facade.resetParam();

    float rotate_x = 45.0f, rotate_y = 90.0f, rotate_z = 180.0f;
    facade.rotateFigure(rotate_x, rotate_y, rotate_z);

    s21::Parameters *params = facade.getParam();
    EXPECT_FLOAT_EQ(params->rotate_x, rotate_x);
    EXPECT_FLOAT_EQ(params->rotate_y, rotate_y);
    EXPECT_FLOAT_EQ(params->rotate_z, rotate_z);
}

// Тест: Масштабирование фигуры
TEST(FacadeTest, ScaleFigureTest) {
    s21::Facade facade;
    facade.resetParam();

    float scale_x = 2.0f, scale_y = 2.0f, scale_z = 2.0f;
    facade.scaleFigure(scale_x, scale_y, scale_z);

    s21::Parameters *params = facade.getParam();
    EXPECT_FLOAT_EQ(params->scale, scale_x);
}

// Тест: Получение фигуры
TEST(FacadeTest, GetFigureTest) {
    s21::Facade facade;
    facade.resetParam();

    EXPECT_NE(facade.getFigure(), nullptr);
}

// Тест: Размеры вершин и граней
TEST(FacadeTest, GetSizeVerticesAndFacetsTest) {
    s21::Facade facade;

    ASSERT_NO_THROW(facade.loadFile(testFileName));

    EXPECT_GT(facade.getSizeVertices(), 0u);
    EXPECT_GT(facade.getSizeFacets(), 0u);
}
