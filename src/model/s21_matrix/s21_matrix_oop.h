#pragma once

#include <iostream>

class S21Matrix {
private:
  int _rows, _cols;
  double **matrix_;

  void AllocMem(int rows, int cols);
  void FreeMem();
  bool EqSizeMatrix(const S21Matrix &other);
  S21Matrix MinorMatrix(int row_i, int column_j);
  bool IsSquareMatrix();
  void SetNewNatrix(const int NewRow, const int NewCol);

public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  friend S21Matrix operator*(const double num, const S21Matrix &other);
  friend S21Matrix operator*(const S21Matrix &other, const double num);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  double &operator()(int row, int col) const;

  int AccessorRow() const;
  int AccessorCol() const;

  void MutatorRow(const int rows);
  void MutatorCol(const int cols);
};