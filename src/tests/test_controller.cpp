#include <QTextStream>

#include "../controller/controller.h"

#define STEP_MOVE 5

const QString testFileName = "./models_3d/cube.obj";
const QString nonExistentFile = "./models_3d/non_existent.obj";
const QString invalidFileFormat = "./models_3d/invalid_format.txt";

// Тест: Инициализация параметров
TEST(FacadeTest, ResetParamTest) {
  Facade facade;
  facade.resetParam();
  Parameters *params = facade.getParam();

  EXPECT_FLOAT_EQ(params->scale, 1.0f);
  EXPECT_FLOAT_EQ(params->shift_x, 0.0f);
  EXPECT_FLOAT_EQ(params->shift_y, 0.0f);
  EXPECT_FLOAT_EQ(params->shift_z, 0.0f);
  EXPECT_FLOAT_EQ(params->rotate_x, 0.0f);
  EXPECT_FLOAT_EQ(params->rotate_y, 0.0f);
  EXPECT_FLOAT_EQ(params->rotate_z, 0.0f);
  EXPECT_EQ(params->type_projection, ProjectionType::Parallel);
}

// Тест: Загрузка корректного файла
TEST(FacadeTest, LoadFileTest) {
  Facade facade;

  ASSERT_NO_THROW(facade.loadFile(testFileName));

  EXPECT_EQ(facade.getParam()->filename, testFileName);
  EXPECT_GT(facade.getSizeVertices(), 0u);
  EXPECT_GT(facade.getSizeFacets(), 0u);
}

// Тест: Перемещение фигуры
TEST(FacadeTest, MoveFigureTest) {
  Facade facade;
  facade.resetParam();

  float move_x = 10.0f, move_y = 20.0f, move_z = 30.0f;
  facade.moveFigure(move_x, move_y, move_z);

  Parameters *params = facade.getParam();
  EXPECT_FLOAT_EQ(params->shift_x, move_x);
  EXPECT_FLOAT_EQ(params->shift_y, move_y);
  EXPECT_FLOAT_EQ(params->shift_z, move_z);
}

// Тест: Проверка координат после перемещения
TEST(FacadeTest, MoveFigureTest2) {
  Facade facade;
  facade.resetParam();
  facade.loadFile(testFileName);

  float move_x = 2.0f, move_y = 3.0f, move_z = -7.0f;
  const auto &copy_vertices = facade.getFigure()->getVertices();
  facade.moveFigure(move_x, move_y, move_z);

  const auto &vertices = facade.getFigure()->getVertices();
  for (long long i = 0; i < vertices.size(); i++) {
    EXPECT_FLOAT_EQ(vertices[i].x(), copy_vertices[i].x() + move_x / STEP_MOVE);
    EXPECT_FLOAT_EQ(vertices[i].y(), copy_vertices[i].y() + move_y / STEP_MOVE);
    EXPECT_FLOAT_EQ(vertices[i].z(), copy_vertices[i].z() + move_z / STEP_MOVE);
  }
}

// Тест: Вращение фигуры
TEST(FacadeTest, RotateFigureTest) {
  Facade facade;
  facade.resetParam();

  float rotate_x = 45.0f, rotate_y = 90.0f, rotate_z = 180.0f;
  facade.rotateFigure(rotate_x, rotate_y, rotate_z);

  Parameters *params = facade.getParam();
  EXPECT_FLOAT_EQ(params->rotate_x, rotate_x);
  EXPECT_FLOAT_EQ(params->rotate_y, rotate_y);
  EXPECT_FLOAT_EQ(params->rotate_z, rotate_z);
}

// Тест: Проверка координат после вращения
TEST(FacadeTest, RotateFigureTest2) {
  Facade facade;
  facade.resetParam();
  facade.loadFile(testFileName);
  const auto &copy_vertices = facade.getFigure()->getVertices();

  float rotate_x = 45.0f, rotate_y = 90.0f, rotate_z = 30.0f;
  facade.rotateFigure(rotate_x, rotate_y, rotate_z);

  const auto &vertices = facade.getFigure()->getVertices();
  float a = rotate_x * M_PI / 180.0f;
  float b = rotate_y * M_PI / 180.0f;
  float c = rotate_z * M_PI / 180.0f;
  for (long long i = 0; i < vertices.size(); i++) {
    EXPECT_FLOAT_EQ(vertices[i].x(),
                    copy_vertices[i].x() * cos(b) * cos(c) +
                        copy_vertices[i].y() *
                            (sin(a) * sin(b) * cos(c) + sin(c) * cos(a)) +
                        copy_vertices[i].z() *
                            (sin(a) * sin(c) - sin(b) * cos(a) * cos(c)));

    EXPECT_FLOAT_EQ(vertices[i].y(),
                    copy_vertices[i].x() * (-sin(c) * cos(b)) +
                        copy_vertices[i].y() *
                            (-sin(a) * sin(b) * sin(c) + cos(a) * cos(c)) +
                        copy_vertices[i].z() *
                            (sin(a) * cos(c) + sin(b) * sin(c) * cos(a)));
    EXPECT_FLOAT_EQ(vertices[i].z(),
                    copy_vertices[i].x() * sin(b) +
                        copy_vertices[i].y() * (-sin(a) * cos(b)) +
                        copy_vertices[i].z() * cos(a) * cos(b));
  }
}

// Тест: Масштабирование фигуры
TEST(FacadeTest, ScaleFigureTest) {
  Facade facade;
  facade.resetParam();

  float scale = 2.0f;
  facade.scaleFigure(scale, scale, scale);

  Parameters *params = facade.getParam();
  EXPECT_FLOAT_EQ(params->scale, scale);
}

// Тест: Проверка координат после масштабирования
TEST(FacadeTest, ScaleFigureTest2) {
  Facade facade;
  facade.resetParam();

  float scale = 2.0f;
  facade.loadFile(testFileName);
  const auto &copy_vertices = facade.getFigure()->getVertices();
  facade.scaleFigure(scale, scale, scale);
  const auto &vertices = facade.getFigure()->getVertices();
  for (long long i = 0; i < vertices.size(); i++) {
    EXPECT_FLOAT_EQ(vertices[i].x(), copy_vertices[i].x() * scale);
    EXPECT_FLOAT_EQ(vertices[i].y(), copy_vertices[i].y() * scale);
    EXPECT_FLOAT_EQ(vertices[i].z(), copy_vertices[i].z() * scale);
  }
}

// Тест: Получение фигуры
TEST(FacadeTest, GetFigureTest) {
  Facade facade;
  facade.resetParam();

  EXPECT_NE(facade.getFigure(), nullptr);
}

// Тест: Размеры вершин и граней
TEST(FacadeTest, GetSizeVerticesAndFacetsTest) {
  Facade facade;

  ASSERT_NO_THROW(facade.loadFile(testFileName));

  EXPECT_GT(facade.getSizeVertices(), 0u);
  EXPECT_GT(facade.getSizeFacets(), 0u);
}

// Тест: Обработка загрузки несуществующего файла
TEST(FacadeTest, LoadNonExistentFileTest) {
  Facade facade;
  try {
    facade.loadFile(nonExistentFile);
    FAIL() << "Expected std::runtime_error";
  } catch (const std::runtime_error &e) {
    EXPECT_STREQ(e.what(), "Cannot open file: ./models_3d/non_existent.obj");
  } catch (...) {
    FAIL() << "Expected std::runtime_error";
  }
}

// Тест: Обработка файла с неправильным форматом
TEST(FacadeTest, LoadInvalidFileFormatTest) {
  Facade facade;
  QFile file(invalidFileFormat);
  if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    QTextStream out(&file);
    out << "This is an invalid format file.\n";
    out << "It doesn't follow the .obj file structure.\n";
    file.close();
  } else {
    FAIL() << "Could not create invalid vertex file for testing.";
  }
  facade.loadFile(invalidFileFormat);

  EXPECT_EQ(facade.getSizeVertices(), 0u);
  EXPECT_EQ(facade.getSizeFacets(), 0u);
  QFile::remove(invalidFileFormat);
}

// Тест: Изменение типа проекции
TEST(FacadeTest, ChangeProjectionTypeTest) {
  Facade facade;
  facade.resetParam();

  EXPECT_EQ(facade.getParam()->type_projection, ProjectionType::Parallel);

  facade.getParam()->type_projection = ProjectionType::Central;
  EXPECT_EQ(facade.getParam()->type_projection, ProjectionType::Central);

  facade.getParam()->type_projection = ProjectionType::Parallel;
  EXPECT_EQ(facade.getParam()->type_projection, ProjectionType::Parallel);
}

// Тест: Обработка пустого файла
TEST(FacadeTest, LoadEmptyFileTest) {
  Facade facade;
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
  QFile::remove(emptyFileName);
}

// Тест: Перемещение с нулевыми значениями
TEST(FacadeTest, MoveFigureWithZeroValues) {
  Facade facade;
  facade.resetParam();

  facade.moveFigure(0.0f, 0.0f, 0.0f);

  Parameters *params = facade.getParam();
  EXPECT_FLOAT_EQ(params->shift_x, 0.0f);
  EXPECT_FLOAT_EQ(params->shift_y, 0.0f);
  EXPECT_FLOAT_EQ(params->shift_z, 0.0f);
}

// Тест: Загрузка файла с большим количеством вершин и граней
TEST(FacadeTest, LoadLargeFileTest) {
  Facade facade;
  QString largeFileName = "./models_3d/dog.obj";

  ASSERT_NO_THROW(facade.loadFile(largeFileName));

  EXPECT_GT(facade.getSizeVertices(), 1000u);
  EXPECT_GT(facade.getSizeFacets(), 1000u);
}

// Тест: Загрузка файла с некорректными данными (отсутствующие вершины или
// грани)
TEST(FacadeTest, LoadFileWithMissingDataTest) {
  Facade facade;
  QString invalidDataFile = "./models_3d/empty.obj";
  QFile file(invalidDataFile);
  if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    file.close();
  } else {
    FAIL() << "Could not create empty file for testing.";
  }
  ASSERT_NO_THROW(facade.loadFile(invalidDataFile));

  EXPECT_EQ(facade.getSizeVertices(), 0u);
  EXPECT_EQ(facade.getSizeFacets(), 0u);
  QFile::remove(invalidDataFile);
}