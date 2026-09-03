#include "s21_matrix_oop.h"

#include "cstring"

S21Matrix::S21Matrix() {
  cols_ = 0;
  rows_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) { CreateMatrix(rows, cols); }

S21Matrix::S21Matrix(const S21Matrix &o) {
  CreateMatrix(o.rows_, o.cols_);

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = o.matrix_[i][j];
    }
}

S21Matrix::S21Matrix(S21Matrix &&o) {
  if (&o != this) {
    this->rows_ = o.rows_;
    this->cols_ = o.cols_;
    this->matrix_ = o.matrix_;
    o.rows_ = 0;
    o.cols_ = 0;
    o.matrix_ = nullptr;
  }
}

S21Matrix::~S21Matrix() { ClearMatrix(); }

int S21Matrix::GetCols() const { return cols_; }

int S21Matrix::GetRows() const { return rows_; }

void S21Matrix::SetRows(int rows) {
  CheckMatrixValid();

  if (rows < 1) throw rowsError;

  if (rows != rows_) {
    S21Matrix tmp(rows, cols_);

    int min = std::min(rows_, rows);
    for (int i = 0; i < min; i++) {
      for (int j = 0; j < cols_; j++) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = tmp;
  }
};

void S21Matrix::SetCols(int cols) {
  CheckMatrixValid();

  if (cols < 1) throw colsError;

  if (cols != cols_) {
    S21Matrix tmp(rows_, cols);

    int min = std::min(cols_, cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < min; j++) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = tmp;
  }
}

void S21Matrix::PrintMatrix() const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) std::cout << matrix_[i][j] << "\t";
    std::cout << "\n";
  }
  std::cout << "\n";
}

void S21Matrix::CreateMatrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    ClearMatrix();
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double *[rows_]();
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
      for (int j = 0; j < cols_; j++) matrix_[i][j] = 0;
    }
  } else
    throw incorrectMatrix;
}

void S21Matrix::ClearMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

void S21Matrix::CheckMatrixValid() const {
  if (matrix_ == nullptr || cols_ < 1 || rows_ < 1) {
    throw incorrectMatrix;
  }
}

void S21Matrix::CheckMatrixSameSize(const S21Matrix &o) const {
  if (cols_ != o.cols_ || rows_ != o.rows_) {
    throw calcError;
  }
}

void S21Matrix::CheckMatrixMulSize(const S21Matrix &o) const {
  if (cols_ != o.rows_) {
    throw calcError;
  }
}

void S21Matrix::CheckMatrixSquare() const {
  if (cols_ != rows_) {
    throw calcError;
  }
}
