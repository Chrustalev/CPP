#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <iostream>

#include "s21_matrix_oop.h"

TEST(CreateMatrix, DefaultConstructor) {
  S21Matrix m;
  ASSERT_TRUE(m.GetCols() == 0);
  ASSERT_TRUE(m.GetRows() == 0);
}

TEST(CreateMatrix, ParamConstructor) {
  S21Matrix m(2, 2);
  ASSERT_TRUE(m.GetCols() == 2);
  ASSERT_TRUE(m.GetRows() == 2);
}

TEST(CreateMatrix, ParamConstructorThrow) {
  EXPECT_NO_THROW(S21Matrix m0(3, 3));
  EXPECT_THROW(S21Matrix m1(0, 2), std::string);
  EXPECT_THROW(S21Matrix m2(2, 0), std::string);
  EXPECT_THROW(S21Matrix m3(0, 0), std::string);
}

TEST(CreateMatrix, CopyConstructor) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix b(a);

  ASSERT_TRUE(a.EqMatrix(b));
}

TEST(CreateMatrix, RemoveConstructor) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix b(a);
  S21Matrix c = std::move(a);

  ASSERT_TRUE(b.EqMatrix(c));
  ASSERT_TRUE(a.GetCols() == 0);
  ASSERT_TRUE(a.GetRows() == 0);
}

TEST(PrintMatrix, PrintOK) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  a.PrintMatrix();
}

TEST(CheckMatrix, MatrixOK) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix b(1, 1);

  EXPECT_NO_THROW(a.CheckMatrixValid());
  EXPECT_NO_THROW(b.CheckMatrixValid());
}

TEST(CheckMatrix, MatrixFail) {
  S21Matrix a;
  EXPECT_THROW(a.CheckMatrixValid(), std::string);
}

TEST(EqMatrix, MatrixEqual) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  ASSERT_TRUE(a.EqMatrix(b));
}

TEST(EqMatrix, MatrixOperatorEq) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  ASSERT_TRUE(a == b);
}

TEST(EqMatrix, MatrixNotEqual) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  S21Matrix d(2, 3);
  S21Matrix e(3, 2);
  S21Matrix f(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 22;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 11;
  c(0, 1) = 2;
  c(1, 0) = 3;
  c(1, 1) = 4;

  ASSERT_FALSE(a.EqMatrix(b));
  ASSERT_FALSE(a.EqMatrix(c));
  ASSERT_FALSE(a.EqMatrix(d));
  ASSERT_FALSE(a.EqMatrix(e));
  ASSERT_FALSE(a.EqMatrix(f));

  ASSERT_FALSE(a == b);
  ASSERT_FALSE(a == c);
  ASSERT_FALSE(a == d);
  ASSERT_FALSE(a == e);
  ASSERT_FALSE(a == f);
}

TEST(Mutator, SetRows) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix cc(1, 2);
  cc(0, 0) = 1;
  cc(0, 1) = 2;

  S21Matrix cd(3, 2);
  cd(0, 0) = 1;
  cd(0, 1) = 2;
  cd(1, 0) = 3;
  cd(1, 1) = 4;
  cd(2, 0) = 0;
  cd(2, 1) = 0;

  S21Matrix b(a);
  S21Matrix c(a);
  S21Matrix d(a);
  b.SetRows(2);
  c.SetRows(1);
  d.SetRows(3);

  EXPECT_THROW(a.SetRows(0), std::string);
  ASSERT_TRUE(a.EqMatrix(b));
  ASSERT_TRUE(c.EqMatrix(cc));
  ASSERT_TRUE(d.EqMatrix(cd));
}

TEST(Mutator, SetCols) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix cc(2, 1);
  cc(0, 0) = 1;
  cc(1, 0) = 3;

  S21Matrix cd(2, 3);
  cd(0, 0) = 1;
  cd(0, 1) = 2;
  cd(0, 2) = 0;
  cd(1, 0) = 3;
  cd(1, 1) = 4;
  cd(1, 2) = 0;

  S21Matrix b(a);
  S21Matrix c(a);
  S21Matrix d(a);
  b.SetCols(2);
  c.SetCols(1);
  d.SetCols(3);

  EXPECT_THROW(a.SetCols(0), std::string);
  ASSERT_TRUE(a.EqMatrix(b));
  ASSERT_TRUE(c.EqMatrix(cc));
  ASSERT_TRUE(d.EqMatrix(cd));
}

TEST(CalcMatrix, SumOK) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix correct(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 4;
  b(0, 1) = 3;
  b(1, 0) = 2;
  b(1, 1) = 1;

  correct(0, 0) = 5;
  correct(0, 1) = 5;
  correct(1, 0) = 5;
  correct(1, 1) = 5;

  S21Matrix copya = a;

  a.SumMatrix(b);
  S21Matrix r1 = a;
  S21Matrix r2 = copya + b;
  S21Matrix r3 = copya;
  r3 += b;

  ASSERT_TRUE(correct.EqMatrix(r1));
  ASSERT_TRUE(correct.EqMatrix(r2));
  ASSERT_TRUE(correct.EqMatrix(r3));
}

TEST(CalcMatrix, SumMatrixDifSize) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 3);
  S21Matrix c(3, 2);
  S21Matrix d(3, 3);

  EXPECT_THROW(a + b, std::string);
  EXPECT_THROW(a + c, std::string);
  EXPECT_THROW(a + d, std::string);
}

TEST(CalcMatrix, SubOK) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix correct(2, 2);

  a(0, 0) = 5;
  a(0, 1) = 5;
  a(1, 0) = 5;
  a(1, 1) = 5;

  b(0, 0) = 4;
  b(0, 1) = 3;
  b(1, 0) = 2;
  b(1, 1) = 1;

  correct(0, 0) = 1;
  correct(0, 1) = 2;
  correct(1, 0) = 3;
  correct(1, 1) = 4;

  S21Matrix copya = a;

  a.SubMatrix(b);
  S21Matrix r1 = a;
  S21Matrix r2 = copya - b;
  S21Matrix r3 = copya;
  r3 -= b;

  ASSERT_TRUE(correct.EqMatrix(r1));
  ASSERT_TRUE(correct.EqMatrix(r2));
  ASSERT_TRUE(correct.EqMatrix(r3));
}

TEST(CalcMatrix, SubMatrixDifSize) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 3);
  S21Matrix c(3, 2);
  S21Matrix d(3, 3);

  EXPECT_THROW(a - b, std::string);
  EXPECT_THROW(a - c, std::string);
  EXPECT_THROW(a - d, std::string);
}

TEST(CalcMatrix, MulMatrixOK) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  S21Matrix correct(3, 3);

  a(0, 0) = 1;
  a(0, 1) = 0;
  a(1, 0) = 2;
  a(1, 1) = 1;
  a(2, 0) = -1;
  a(2, 1) = 1;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(0, 2) = 0;
  b(1, 0) = 0;
  b(1, 1) = -1;
  b(1, 2) = 1;

  correct(0, 0) = 1;
  correct(0, 1) = 2;
  correct(0, 2) = 0;
  correct(1, 0) = 2;
  correct(1, 1) = 3;
  correct(1, 2) = 1;
  correct(2, 0) = -1;
  correct(2, 1) = -3;
  correct(2, 2) = 1;

  S21Matrix copya = a;

  a.MulMatrix(b);
  S21Matrix r1 = a;
  S21Matrix r2 = copya * b;
  S21Matrix r3 = copya;
  r3 *= b;

  ASSERT_TRUE(correct.EqMatrix(r1));
  ASSERT_TRUE(correct.EqMatrix(r2));
  ASSERT_TRUE(correct.EqMatrix(r3));
}

TEST(CalcMatrix, MulMatrixDifSize) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 3);
  S21Matrix c(3, 2);

  EXPECT_THROW(a * b, std::string);
  EXPECT_NO_THROW(a * c);
}

TEST(CalcMatrix, MulNumberOK) {
  S21Matrix a(3, 2);

  double number = 2.2;
  S21Matrix correct(3, 2);

  a(0, 0) = 1;
  a(0, 1) = 0;
  a(1, 0) = 2;
  a(1, 1) = 1;
  a(2, 0) = -1;
  a(2, 1) = 1;

  correct(0, 0) = 2.2;
  correct(0, 1) = 0;
  correct(1, 0) = 4.4;
  correct(1, 1) = 2.2;

  correct(2, 0) = -2.2;
  correct(2, 1) = 2.2;

  S21Matrix copya = a;

  a.MulNumber(number);
  S21Matrix r1 = a;
  S21Matrix r2 = copya * number;
  S21Matrix r3 = copya;
  r3 *= number;

  ASSERT_TRUE(correct.EqMatrix(r1));
  ASSERT_TRUE(correct.EqMatrix(r2));
  ASSERT_TRUE(correct.EqMatrix(r3));
}

TEST(GetElement, elements) {
  S21Matrix a(2, 3);

  EXPECT_THROW(a(0, -1), std::string);
  EXPECT_THROW(a(0, 3), std::string);
  EXPECT_THROW(a(-1, 0), std::string);
  EXPECT_THROW(a(2, 0), std::string);
  EXPECT_NO_THROW(a(1, 1));
}

TEST(MatrixAdv, Transpose) {
  S21Matrix a(3, 2);
  S21Matrix correct(2, 3);

  a(0, 0) = 1;
  a(0, 1) = 0;
  a(1, 0) = 2;
  a(1, 1) = 1;
  a(2, 0) = -1;
  a(2, 1) = 1;

  correct(0, 0) = 1;
  correct(0, 1) = 2;
  correct(0, 2) = -1;
  correct(1, 0) = 0;
  correct(1, 1) = 1;
  correct(1, 2) = 1;

  S21Matrix b = a.Transpose();

  ASSERT_TRUE(correct.EqMatrix(b));
}

TEST(MatrixAdv, DeterminantOK) {
  S21Matrix a(5, 5);
  S21Matrix b(1, 1);
  S21Matrix c(2, 2);

  a(0, 0) = 3;
  a(0, 1) = -1;
  a(0, 2) = 2;
  a(0, 3) = -1;
  a(0, 4) = 1;

  a(1, 0) = 5;
  a(1, 1) = 1;
  a(1, 2) = -2;
  a(1, 3) = 1;
  a(1, 4) = 2;

  a(2, 0) = 9;
  a(2, 1) = -1;
  a(2, 2) = 1;
  a(2, 3) = 3;
  a(2, 4) = 4;

  a(3, 0) = 3;
  a(3, 1) = 0;
  a(3, 2) = 6;
  a(3, 3) = -1;
  a(3, 4) = 3;

  a(4, 0) = 5;
  a(4, 1) = 2;
  a(4, 2) = 3;
  a(4, 3) = -2;
  a(4, 4) = 1;

  b(0, 0) = 3;

  c(0, 0) = 2;
  c(0, 1) = -3;
  c(1, 0) = 5;
  c(1, 1) = 6;

  double r1;
  double r2;
  double r3;

  EXPECT_NO_THROW(r1 = a.Determinant());
  EXPECT_NO_THROW(r2 = b.Determinant());
  EXPECT_NO_THROW(r3 = c.Determinant());
  ASSERT_TRUE(r1 == 465);
  ASSERT_TRUE(r2 == 3);
  ASSERT_TRUE(r3 == 27);
}

TEST(MatrixAdv, DeterminantFail) {
  S21Matrix a(3, 2);
  S21Matrix b;

  EXPECT_THROW(a.Determinant(), std::string);
  EXPECT_THROW(b.Determinant(), std::string);
}

TEST(MatrixAdv, CalcComplementsOK) {
  S21Matrix a(3, 3);
  S21Matrix b(1, 1);
  S21Matrix correct1(3, 3);
  S21Matrix correct2(1, 1);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 0;
  a(1, 1) = 4;
  a(1, 2) = 2;
  a(2, 0) = 5;
  a(2, 1) = 2;
  a(2, 2) = 1;

  b(0, 0) = 3;

  correct1(0, 0) = 0;
  correct1(0, 1) = 10;
  correct1(0, 2) = -20;
  correct1(1, 0) = 4;
  correct1(1, 1) = -14;
  correct1(1, 2) = 8;
  correct1(2, 0) = -8;
  correct1(2, 1) = -2;
  correct1(2, 2) = 4;

  correct2(0, 0) = 1;

  S21Matrix r1 = a.CalcComplements();
  S21Matrix r2 = b.CalcComplements();

  ASSERT_TRUE(correct1.EqMatrix(r1));
  ASSERT_TRUE(correct2.EqMatrix(r2));
}

TEST(MatrixAdv, CalcComplementsFail) {
  S21Matrix a(3, 2);

  EXPECT_THROW(a.CalcComplements(), std::string);
}

TEST(MatrixAdv, InverseMatrixOK) {
  S21Matrix a(3, 3);
  S21Matrix correct(3, 3);

  a(0, 0) = 1;
  a(0, 1) = -2;
  a(0, 2) = 1;
  a(1, 0) = 2;
  a(1, 1) = 1;
  a(1, 2) = -1;
  a(2, 0) = 3;
  a(2, 1) = 2;
  a(2, 2) = -2;

  correct(0, 0) = 0;
  correct(0, 1) = 2;
  correct(0, 2) = -1;
  correct(1, 0) = -1;
  correct(1, 1) = 5;
  correct(1, 2) = -3;
  correct(2, 0) = -1;
  correct(2, 1) = 8;
  correct(2, 2) = -5;

  S21Matrix r = a.InverseMatrix();
  ASSERT_TRUE(correct.EqMatrix(r));
}

TEST(MatrixAdv, InverseMatrixFail) {
  S21Matrix a(3, 3);

  S21Matrix b(3, 2);

  a(0, 0) = 4;
  a(0, 1) = 2;
  a(0, 2) = -3;
  a(1, 0) = -8;
  a(1, 1) = -7;
  a(1, 2) = 1;
  a(2, 0) = 4;
  a(2, 1) = 2;
  a(2, 2) = -3;

  EXPECT_THROW(a.InverseMatrix(), std::string);
  EXPECT_THROW(b.InverseMatrix(), std::string);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}