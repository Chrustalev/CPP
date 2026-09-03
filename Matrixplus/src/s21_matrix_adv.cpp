#include "cstring"
#include "math.h"
#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Transpose() {
  this->CheckMatrixValid();

  S21Matrix transpose(cols_, rows_);

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) transpose.matrix_[j][i] = matrix_[i][j];

  return transpose;
}

// Возвращаетновюу  матрицу без row-ой строки и col-того столбца
S21Matrix S21Matrix::GetSubMatrix(int row, int col) {
  this->CheckMatrixValid();

  int size = rows_;

  S21Matrix subMatrix(rows_ - 1, cols_ - 1);

  int offsetRow = 0;

  for (int i = 0; i < size - 1; i++) {
    if (i == row) offsetRow = 1;

    int offsetCol = 0;
    for (int j = 0; j < size - 1; j++) {
      if (j == col) offsetCol = 1;
      subMatrix.matrix_[i][j] = matrix_[i + offsetRow][j + offsetCol];
    }
  }
  return subMatrix;
}

// Вычисление определителя матрицы разложение по первой строке
double s21_recursionDet(S21Matrix m) {
  double det = 0;
  int degree = 1;  // (-1)^(1+j) из формулы определителя
  int size = m.GetRows();

  // Условие выхода из рекурсии
  if (size == 1)
    det = m(0, 0);
  else if (size == 2)
    det = m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
  else if (size > 2) {
    for (int j = 0; j < size; j++) {
      S21Matrix subMatrix = m.GetSubMatrix(0, j);
      det = det + (degree * m(0, j) * s21_recursionDet(subMatrix));
      degree = -degree;
    }
  }

  return det;
}

double S21Matrix::Determinant() const {
  this->CheckMatrixValid();
  this->CheckMatrixSquare();

  return s21_recursionDet(*this);
}

S21Matrix S21Matrix::CalcComplements() {
  this->CheckMatrixValid();
  this->CheckMatrixSquare();

  S21Matrix complements(cols_, rows_);
  if (this->rows_ > 1) {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) {
        S21Matrix subMatrix = this->GetSubMatrix(i, j);
        double deter = subMatrix.Determinant();

        int ed = pow(-1, i + j);
        complements.matrix_[i][j] = deter * ed;
      }
  } else if (this->rows_ == 1)
    complements.matrix_[0][0] = 1;

  return complements;
}

S21Matrix S21Matrix::InverseMatrix() {
  this->CheckMatrixValid();
  this->CheckMatrixSquare();

  S21Matrix c = this->CalcComplements();
  S21Matrix t = c.Transpose();
  double deter = this->Determinant();

  if (fabs(deter) < 1e-7)
    throw calcError;
  else
    t.MulNumber(1.0 / deter);
  return t;
}