#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>

const std::string incorrectMatrix{"Incorrect Matrix"};
const std::string calcError{"Calculation error"};
const std::string indexError{"Index out of range"};
const std::string colsError{"Cols out of range"};
const std::string rowsError{"Rows out of range"};

class S21Matrix {
 private:
  int rows_ = 0, cols_ = 0;
  double** matrix_ = nullptr;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& o);
  S21Matrix(S21Matrix&& o);
  ~S21Matrix();

  int GetCols() const;
  int GetRows() const;
  void SetRows(int rows);
  void SetCols(int cols);

  void CheckMatrixValid() const;
  void CheckMatrixSameSize(const S21Matrix& o) const;
  void CheckMatrixMulSize(const S21Matrix& o) const;
  void CheckMatrixSquare() const;
  void CreateMatrix(int rows, int cols);
  void ClearMatrix();
  void PrintMatrix() const;
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulMatrix(const S21Matrix& other);
  void MulNumber(const double num);

  S21Matrix operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);

  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);

  S21Matrix operator*(const double number);
  S21Matrix& operator*=(const double number);

  S21Matrix operator*(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);

  bool operator==(const S21Matrix& other) const;

  double& operator()(int i, int j) const;

  S21Matrix Transpose();

  S21Matrix GetSubMatrix(int row, int col);

  double Determinant() const;
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
};

#endif
