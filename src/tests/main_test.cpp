#include <gtest/gtest.h>

// Подключение всех файлов тестов
#include "test_figure.cpp"
#include "test_parser.cpp"
#include "test_transform_figure.cpp"
#include "test_transform_matrix.cpp"
#include "test_transform_matrix_builder.cpp"

// Определение main для тестов
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
