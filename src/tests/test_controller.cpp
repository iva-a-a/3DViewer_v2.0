#include <gtest/gtest.h>
#include "../controller/controller.h"

const QString testFileName = "./models_3d/cube.obj";
const QString nonExistentFile = "./models_3d/non_existent.obj";
const QString invalidFileFormat = "./models_3d/invalid_format.txt";

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

// Тест: Загрузка корректного файла
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

    float scale = 2.0f;
    facade.scaleFigure(scale, scale, scale);

    s21::Parameters *params = facade.getParam();
    EXPECT_FLOAT_EQ(params->scale, scale);
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

// Тест: Обработка загрузки несуществующего файла
TEST(FacadeTest, LoadNonExistentFileTest) {
    s21::Facade facade;
    QString nonExistentFile = "./models_3d/non_existent.obj";
    try {
        facade.loadFile(nonExistentFile);
        FAIL() << "Expected std::runtime_error";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Cannot open file: ./models_3d/non_existent.obj");
    } catch (...) {
        FAIL() << "Expected std::runtime_error";
    }
}

// Тест: Обработка файла с неправильным форматом
TEST(FacadeTest, LoadInvalidFileFormatTest) {
    s21::Facade facade;
    
    facade.loadFile(invalidFileFormat);

    EXPECT_EQ(facade.getSizeVertices(), 0u);
    EXPECT_EQ(facade.getSizeFacets(), 0u);
}

// Тест: Изменение типа проекции
TEST(FacadeTest, ChangeProjectionTypeTest) {
    s21::Facade facade;
    facade.resetParam();

    EXPECT_EQ(facade.getParam()->type_projection, s21::ProjectionType::Parallel);

    facade.getParam()->type_projection = s21::ProjectionType::Central;
    EXPECT_EQ(facade.getParam()->type_projection, s21::ProjectionType::Central);

    facade.getParam()->type_projection = s21::ProjectionType::Parallel;
    EXPECT_EQ(facade.getParam()->type_projection, s21::ProjectionType::Parallel);
}

// Тест: Обработка пустого файла
TEST(FacadeTest, LoadEmptyFileTest) {
    s21::Facade facade;
    QString emptyFileName = "./models_3d/empty.obj";
    QFile file(emptyFileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.close();
    } else {
        FAIL() << "Could not create empty file for testing.";
    }

    ASSERT_NO_THROW(facade.loadFile(emptyFileName));
    EXPECT_EQ(facade.getSizeVertices(), 0u);
    EXPECT_EQ(facade.getSizeFacets(), 0u);
}

// Тест: Перемещение с нулевыми значениями
TEST(FacadeTest, MoveFigureWithZeroValues) {
    s21::Facade facade;
    facade.resetParam();

    facade.moveFigure(0.0f, 0.0f, 0.0f);

    s21::Parameters *params = facade.getParam();
    EXPECT_FLOAT_EQ(params->shift_x, 0.0f);
    EXPECT_FLOAT_EQ(params->shift_y, 0.0f);
    EXPECT_FLOAT_EQ(params->shift_z, 0.0f);
} 

// Тест: Загрузка файла с большим количеством вершин и граней
TEST(FacadeTest, LoadLargeFileTest) {
    s21::Facade facade;
    QString largeFileName = "./models_3d/dog.obj";

    ASSERT_NO_THROW(facade.loadFile(largeFileName));

    EXPECT_GT(facade.getSizeVertices(), 1000u); 
    EXPECT_GT(facade.getSizeFacets(), 1000u);   
}

// Тест: Загрузка файла с некорректными данными (отсутствующие вершины или грани)
TEST(FacadeTest, LoadFileWithMissingDataTest) {
    s21::Facade facade;
    QString invalidDataFile = "./models_3d/empty.obj";

    ASSERT_NO_THROW(facade.loadFile(invalidDataFile));

    EXPECT_EQ(facade.getSizeVertices(), 0u); 
    EXPECT_EQ(facade.getSizeFacets(), 0u);   
} 

// Тест: Загрузка файла с дублирующимися вершинами или гранями
TEST(FacadeTest, LoadFileWithDuplicatesTest) {
    s21::Facade facade;
    QString duplicatesFile = "./models_3d/duplicates.obj";

    ASSERT_NO_THROW(facade.loadFile(duplicatesFile));

    EXPECT_GT(facade.getSizeVertices(), 0u); 
    EXPECT_GT(facade.getSizeFacets(), 0u);   
}