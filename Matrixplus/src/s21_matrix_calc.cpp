#include "cstring"
#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) return false;

  bool result = true;
  for (int i = 0; i < rows_ && result; i++)
    for (int j = 0; j < cols_ && result; j++)
      result = matrix_[i][j] == other.matrix_[i][j];

  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  this->CheckMatrixValid();
  other.CheckMatrixValid();
  CheckMatrixSameSize(other);

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  this->CheckMatrixValid();
  other.CheckMatrixValid();
  CheckMatrixSameSize(other);

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  this->CheckMatrixValid();
  other.CheckMatrixValid();
  CheckMatrixMulSize(other);

  S21Matrix mulMatrix(rows_, other.cols_);

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      for (int k = 0; k < other.rows_; k++)
        mulMatrix.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];

  *this = mulMatrix;
}

void S21Matrix::MulNumber(const double num) {
  this->CheckMatrixValid();

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

S21Matrix S21Matrix::operator=(const S21Matrix &other) {
  CreateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }

  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  // вызов конструктора копирования
  // теперь result равен первой матрице в операции сложения
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double number) {
  S21Matrix result = *this;
  result.MulNumber(number);
  return result;
}

S21Matrix &S21Matrix::operator*=(const double number) {
  MulNumber(number);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

double &S21Matrix::operator()(int i, int j) const {
  this->CheckMatrixValid();

  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw indexError;
  }
  return matrix_[i][j];
}
