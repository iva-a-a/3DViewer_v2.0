#pragma once

#include <cmath>
#include <iostream>

/**
 * @class S21Matrix
 * @brief Класс для работы с матрицами.
 */
class S21Matrix {
private:
  /** Количество строк матрицы. */
  int _rows;
  /** Количество столбцов матрицы. */
  int _cols;
  /** Указатель на двумерный массив для хранения элементов
                       матрицы. */
  double **matrix_;

  /**
   * @brief Выделение памяти для двумерного массива матрицы.
   * @param rows Количество строк матрицы.
   * @param cols Количество столбцов матрицы.
   */
  void AllocMem(int rows, int cols);
  /**
   * @brief Освобождение память, занятую матрицей.
   */
  void FreeMem();
  /**
   * @brief Проверка, имеют ли две матрицы одинаковый размер.
   * @param other Вторая матрица для сравнения.
   * @return true Если размеры матриц равны; false в противном случае.
   */
  bool EqSizeMatrix(const S21Matrix &other);
  /**
   * @brief Вычисление минора матрицы.
   * @param row_i Индекс строки, которую нужно удалить.
   * @param column_j Индекс столбца, который нужно удалить.
   * @return Возвращает новую матрицу, представляющую минор.
   */
  S21Matrix MinorMatrix(int row_i, int column_j);
  /**
   * @brief Проверка, является ли матрица квадратной.
   * @return true Если матрица квадратная; false в противном случае.
   */
  bool IsSquareMatrix();
  /**
   * @brief Установка нового размера матрицы.
   * @param NewRow Новое количество строк матрицы.
   * @param NewCol Новое количество столбцов матрицы.
   */
  void SetNewNatrix(const int NewRow, const int NewCol);

public:
  /**
   * @brief Конструктор S21Matrix по умолчанию.
   */
  S21Matrix();
  /**
   * @brief Конструктор S21Matrix с параметрами.
   * @param rows Количество строк.
   * @param cols Количество столбцов.
   */
  S21Matrix(int rows, int cols);
  /**
   * @brief Конструктор копирования S21Matrix.
   * @param other Другой объект S21Matrix для копирования.
   */
  S21Matrix(const S21Matrix &other);
  /**
   * @brief Конструктор перемещения.
   * @param other Другой объект S21Matrix для перемещения.
   */
  S21Matrix(S21Matrix &&other);
  /**
   * @brief Деструктор S21Matrix.
   */
  ~S21Matrix();

  /**
   * @brief Проверка на равенство матриц.
   * @param other Вторая матрица для сравнения.
   * @return true, если матрицы равны; false в противном случае.
   */
  bool EqMatrix(const S21Matrix &other);
  /**
   * @brief Сложение матриц.
   * @param other Вторая матрица для сложения.
   */
  void SumMatrix(const S21Matrix &other);
  /**
   * @brief Вычитание матриц.
   * @param other Вторая матрица для вычитания.
   */
  void SubMatrix(const S21Matrix &other);
  /**
   * @brief Умножение матрицы на число.
   * @param num Число, на которое умножается матрица.
   */
  void MulNumber(const double num);
  /**
   * @brief Умножение матриц.
   * @param other Вторая матрица для умножения.
   */
  void MulMatrix(const S21Matrix &other);
  /**
   * @brief Транспонирование матрицы.
   * @return Транспонированная матрица.
   */
  S21Matrix Transpose();
  /**
   * @brief Вычисление матрицы алгебраических дополнений.
   * @return Матрица алгебраических дополнений.
   */
  S21Matrix CalcComplements();
  /**
   * @brief Вычисление определителя матрицы.
   * @return Значение определителя.
   */
  double Determinant();
  /**
   * @brief Вычисление обратной матрицы.
   * @return Обратная матрица.
   */
  S21Matrix InverseMatrix();

  /**
   * @brief Оператор сложения матриц.
   * @param other Вторая матрица для сложения.
   * @return Результирующая матрица, представляющая собой сумму двух матриц.
   */
  S21Matrix operator+(const S21Matrix &other);
  /**
   * @brief Оператор вычитания матриц.
   * @param other Вторая матрица для вычитания.
   * @return Результирующая матрица, представляющая собой разность двух матриц.
   */
  S21Matrix operator-(const S21Matrix &other);
  /**
   * @brief Оператор умножения матриц.
   * @param other Вторая матрица для умножения.
   * @return Результирующая матрица, представляющая собой произведение двух
   * матриц.
   */
  S21Matrix operator*(const S21Matrix &other);
  /**
   * @brief Оператор умножения матрицы на число (слева).
   * @param num Число, на которое необходимо умножить матрицу.
   * @param other Матрица, которую необходимо умножить на число.
   * @return Результирующая матрица, представляющая собой произведение матрицы
   * на число слева.
   */
  friend S21Matrix operator*(const double num, const S21Matrix &other);
  /**
   * @brief Оператор умножения матрицы на число (справа).
   * @param num Число, на которое необходимо умножить матрицу.
   * @param other Матрица, которую необходимо умножить на число.
   * @return Результирующая матрица, представляющая собой произведение матрицы
   * на число справа.
   */
  friend S21Matrix operator*(const S21Matrix &other, const double num);
  /**
   * @brief Оператор сравнения матриц.
   * @param other Вторая матрица для сравнения.
   * @return Возвращает true, если матрицы равны; false в противном случае.
   */
  bool operator==(const S21Matrix &other);
  /**
   * @brief Оператор присваивания (копирования).
   * @param other Матрица, которую необходимо скопировать.
   * @return Ссылка на текущий объект матрицы после присваивания.
   */
  S21Matrix &operator=(const S21Matrix &other);
  /**
   * @brief Оператор присваивания (перемещения).
   * @param other Матрица, которую необходимо переместить.
   * @return Ссылка на текущий объект матрицы после присваивания.
   */
  S21Matrix &operator=(S21Matrix &&other);
  /**
   * @brief Оператор сложения с присваиванием.
   * @param other Вторая матрица, которую необходимо сложить с текущей.
   * @return Ссылка на текущий объект матрицы после операции.
   */
  S21Matrix &operator+=(const S21Matrix &other);
  /**
   * @brief Оператор вычитания с присваиванием.
   * @param other Матрица, которую необходимо вычесть из текущей.
   * @return Ссылка на текущий объект матрицы после операции.
   */
  S21Matrix &operator-=(const S21Matrix &other);
  /**
   * @brief Оператор умножения с присваиванием.
   * @param other Вторая матрица, которую необходимо умножить на текущую.
   * @return Ссылка на текущий объект матрицы после операции.
   */
  S21Matrix &operator*=(const S21Matrix &other);
  /**
   * @brief Оператор умножения на число с присваиванием.
   * @param num Число, на которое необходимо умножить матрицу.
   * @return Ссылка на текущий объект матрицы после операции.
   */
  S21Matrix &operator*=(const double num);
  /**
   * @brief Оператор доступа к элементам матрицы.
   * @param row Индекс строки.
   * @param col Индекс столбца.
   * @return Ссылка на элемент матрицы по заданным индексам.
   */
  double &operator()(int row, int col) const;

  /**
   * @brief Получение количества строк.
   * @return Количество строк.
   */
  int AccessorRow() const;
  /**
   * @brief Получение количества столбцов.
   * @return Количество столбцов.
   */
  int AccessorCol() const;

  /**
   * @brief Установка нового количества строк.
   * @param rows Новое количество строк.
   */
  void MutatorRow(const int rows);
  /**
   * @brief Установка нового количества столбцов.
   * @param cols Новое количество столбцов.
   */
  void MutatorCol(const int cols);
};