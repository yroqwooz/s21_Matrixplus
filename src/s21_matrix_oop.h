#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <math.h>
#include <string.h>

#include <iostream>
#include <memory>

class S21Matrix final {
 private:
  int rows_, cols_;
  double** matrix_;

  S21Matrix CalcMinorMat(int i_ignore, int j_ignore);
  void SwapRows(int row1, int row2) noexcept;
  bool CheckMatrix(const S21Matrix& other) const noexcept;
  void AllocateMatrix();
  void FreeMatrix();
  void FillWithZeroes() noexcept;

 public:
  S21Matrix() noexcept;
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  double& operator()(int row, int col);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  bool operator==(const S21Matrix& other) const noexcept;

  void SwapMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  const int& GetRows() const noexcept;
  const int& GetCols() const noexcept;
  void SetRows(int rows_);
  void SetCols(int cols_);
};

namespace s21 {
enum { FAILED, PASSED };
};

#endif  //__S21MATRIX_H__