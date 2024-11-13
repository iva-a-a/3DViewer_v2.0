#include "test_3dviewer.h"

TEST(Tests1, TestReadFile) {
  s21::ObjModel model;
  QString filename = "./tests/cube.obj";

  model.recordCoordFromFile(filename);

  EXPECT_EQ(model.getVertices().size(), 8);

  ASSERT_EQ(model.getVertices()[0].x(), 1.0f);
  ASSERT_EQ(model.getVertices()[0].y(), -1.0f);
  ASSERT_EQ(model.getVertices()[0].z(), -1.0f);

  ASSERT_EQ(model.getVertices()[1].x(), 1.0f);
  ASSERT_EQ(model.getVertices()[1].y(), -1.0f);
  ASSERT_EQ(model.getVertices()[1].z(), 1.0f);

  ASSERT_EQ(model.getVertices()[2].x(), -1.0f);
  ASSERT_EQ(model.getVertices()[2].y(), -1.0f);
  ASSERT_EQ(model.getVertices()[2].z(), 1.0f);

  ASSERT_EQ(model.getVertices()[3].x(), -1.0f);
  ASSERT_EQ(model.getVertices()[3].y(), -1.0f);
  ASSERT_EQ(model.getVertices()[3].z(), -1.0f);

  ASSERT_EQ(model.getVertices()[4].x(), 1.0f);
  ASSERT_EQ(model.getVertices()[4].y(), 1.0f);
  ASSERT_NEAR(model.getVertices()[4].z(), -0.999999, 1e-6);

  ASSERT_NEAR(model.getVertices()[5].x(), 0.999999, 1e-6);
  ASSERT_EQ(model.getVertices()[5].y(), 1.0f);
  ASSERT_NEAR(model.getVertices()[5].z(), 1.000001, 1e-6);

  ASSERT_EQ(model.getVertices()[6].x(), -1.0f);
  ASSERT_EQ(model.getVertices()[6].y(), 1.0f);
  ASSERT_EQ(model.getVertices()[6].z(), 1.0f);

  ASSERT_EQ(model.getVertices()[7].x(), -1.0f);
  ASSERT_EQ(model.getVertices()[7].y(), 1.0f);
  ASSERT_EQ(model.getVertices()[7].z(), -1.0f);

  ASSERT_EQ(model.getFacets().size(), 12);
  for (int i = 0; i < 12; i++) {
    ASSERT_EQ(model.getFacets()[i].size(), 3);
  }

  ASSERT_EQ(model.getFacets()[0][0], 1);
  ASSERT_EQ(model.getFacets()[0][1], 2);
  ASSERT_EQ(model.getFacets()[0][2], 3);

  ASSERT_EQ(model.getFacets()[1][0], 7);
  ASSERT_EQ(model.getFacets()[1][1], 6);
  ASSERT_EQ(model.getFacets()[1][2], 5);

  ASSERT_EQ(model.getFacets()[2][0], 4);
  ASSERT_EQ(model.getFacets()[2][1], 5);
  ASSERT_EQ(model.getFacets()[2][2], 1);

  ASSERT_EQ(model.getFacets()[3][0], 5);
  ASSERT_EQ(model.getFacets()[3][1], 6);
  ASSERT_EQ(model.getFacets()[3][2], 2);

  ASSERT_EQ(model.getFacets()[4][0], 2);
  ASSERT_EQ(model.getFacets()[4][1], 6);
  ASSERT_EQ(model.getFacets()[4][2], 7);

  ASSERT_EQ(model.getFacets()[5][0], 0);
  ASSERT_EQ(model.getFacets()[5][1], 3);
  ASSERT_EQ(model.getFacets()[5][2], 7);

  ASSERT_EQ(model.getFacets()[6][0], 0);
  ASSERT_EQ(model.getFacets()[6][1], 1);
  ASSERT_EQ(model.getFacets()[6][2], 3);

  ASSERT_EQ(model.getFacets()[7][0], 4);
  ASSERT_EQ(model.getFacets()[7][1], 7);
  ASSERT_EQ(model.getFacets()[7][2], 5);

  ASSERT_EQ(model.getFacets()[8][0], 0);
  ASSERT_EQ(model.getFacets()[8][1], 4);
  ASSERT_EQ(model.getFacets()[8][2], 1);

  ASSERT_EQ(model.getFacets()[9][0], 1);
  ASSERT_EQ(model.getFacets()[9][1], 5);
  ASSERT_EQ(model.getFacets()[9][2], 2);

  ASSERT_EQ(model.getFacets()[10][0], 3);
  ASSERT_EQ(model.getFacets()[10][1], 2);
  ASSERT_EQ(model.getFacets()[10][2], 7);

  ASSERT_EQ(model.getFacets()[11][0], 4);
  ASSERT_EQ(model.getFacets()[11][1], 0);
  ASSERT_EQ(model.getFacets()[11][2], 7);
}