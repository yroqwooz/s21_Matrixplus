#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

#define EPS 1e-7
#define SUCCESS 1
#define FAILURE 0

TEST(Constructor, NoPars_1) {
  S21Matrix Matrix;
  ASSERT_EQ(Matrix.GetCols(), 0);
  ASSERT_EQ(Matrix.GetRows(), 0);
}

TEST(Constructor, NoPars_2) {
  auto test = S21Matrix();
  ASSERT_EQ(test.GetRows(), 0);
  ASSERT_EQ(test.GetCols(), 0);
}

TEST(Constructor, Pars_1) {
  S21Matrix Matrix(5, 5);
  ASSERT_EQ(Matrix.GetRows(), 5);
  ASSERT_EQ(Matrix.GetCols(), 5);
  Matrix(3, 2) = 6.54321;
  ASSERT_DOUBLE_EQ(Matrix(3, 2), 6.54321);
}

TEST(Constructor, Pars_2) {
  auto test = S21Matrix(3, 3);
  ASSERT_EQ(test.GetRows(), 3);
  ASSERT_EQ(test.GetCols(), 3);
}

TEST(Constructor, Pars_Negative) {
  ASSERT_ANY_THROW(S21Matrix Matrix(0, -243));
}

TEST(Constructor, Copy_1) {
  S21Matrix Matrix(2, 2);
  for (int i = 0; i < Matrix.GetRows(); i++) {
    for (int j = 0; j < Matrix.GetCols(); j++) {
      Matrix(i, j) = 3.14;
    }
  }
  S21Matrix Matrix2(Matrix);
  for (int i = 0; i < Matrix.GetRows(); i++) {
    for (int j = 0; j < Matrix.GetCols(); j++) {
      ASSERT_EQ(Matrix(i, j), Matrix2(i, j));
    }
  }
}

TEST(Constructor, Copy_2) {
  S21Matrix M1(2, 2);
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      M1(i, j) = 3.15;
    }
  }
  S21Matrix M2 = M1;
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      ASSERT_EQ(M1(i, j), M2(i, j));
    }
  }
}

TEST(Constructor, Copy_3) {
  auto test = S21Matrix(3, 3);
  test(0, 0) = 1;
  auto temp = S21Matrix(test);
  ASSERT_TRUE(test == temp);
}

TEST(Constructor, Move_1) {
  S21Matrix M1(2, 2);
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      M1(i, j) = 3.15;
    }
  }
  S21Matrix M2 = std::move(M1);

  ASSERT_EQ(M2.GetRows(), 2);
  ASSERT_EQ(M2.GetCols(), 2);
  ASSERT_EQ(M1.GetRows(), 0);
  ASSERT_EQ(M1.GetCols(), 0);
}

TEST(Constructor, Move_2) {
  S21Matrix M1(2, 2);
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      M1(i, j) = 3.15;
    }
  }
  S21Matrix M2(std::move(M1));

  ASSERT_EQ(M2.GetRows(), 2);
  ASSERT_EQ(M2.GetCols(), 2);
  ASSERT_EQ(M1.GetRows(), 0);
  ASSERT_EQ(M1.GetCols(), 0);
}

TEST(Constructor, Move_3) {
  auto test1 = S21Matrix(3, 3);
  test1(1, 1) = 5;
  auto test2 = S21Matrix(test1);
  auto test3 = S21Matrix(std::move(test1));
  ASSERT_TRUE(test2 == test3);
}

TEST(EqMatrix, Test_1) {
  S21Matrix M(3, 3);
  S21Matrix M2(2, 2);
  ASSERT_EQ(M.EqMatrix(M2), FAILURE);
}

TEST(EqMatrix, Test_2) {
  S21Matrix M(3, 3);
  S21Matrix M2(3, 3);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 3.146743;
    }
  }
  for (int i = 0; i < M2.GetRows(); i++) {
    for (int j = 0; j < M2.GetCols(); j++) {
      M2(i, j) = 3.146743;
    }
  }
  ASSERT_EQ(M.EqMatrix(M2), SUCCESS);
}

TEST(EqMatrix, Test_3) {
  auto test1 = S21Matrix(3, 3);
  test1(1, 2) = 5;
  auto test2 = test1;
  ASSERT_TRUE(test1.EqMatrix(test2));
  ASSERT_TRUE(test1.EqMatrix(test2) == (test1 == test2));
  test2(1, 1) = 1;
  ASSERT_FALSE(test1.EqMatrix(test2));
  ASSERT_TRUE(test1.EqMatrix(test2) == (test1 == test2));
  auto test3 = S21Matrix(5, 5);
  ASSERT_FALSE(test1.EqMatrix(test3));
  ASSERT_TRUE(test1.EqMatrix(test3) == (test1 == test3));
}

TEST(SumMatrix, Test_1) {
  S21Matrix M1(3, 3);
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      M1(i, j) = 2.15;
    }
  }
  S21Matrix M2(M1);
  M2.SumMatrix(M1);
  for (int i = 0; i < M2.GetRows(); i++) {
    for (int j = 0; j < M2.GetCols(); j++) {
      ASSERT_EQ(M2(i, j), 4.3);
    }
  }
}

TEST(SumMatrix, Test_2) {
  S21Matrix M;
  S21Matrix M2(2, 2);
  ASSERT_ANY_THROW(M.SumMatrix(M2));
}

TEST(SumMatrix, Test_3) {
  S21Matrix M1(3, 3);
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      M1(i, j) = 2.15;
    }
  }
  S21Matrix M2(M1);
  M2.SubMatrix(M1);
  for (int i = 0; i < M2.GetRows(); i++) {
    for (int j = 0; j < M2.GetCols(); j++) {
      ASSERT_EQ(M2(i, j), 0);
    }
  }
}

TEST(SumMatrix, Test_4) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;
  auto test2 = test1;
  test1.SumMatrix(test2);
  ASSERT_EQ(test1(0, 0), 2);
}

TEST(SumMatrix, Test_5_notEq) {
  auto test1 = S21Matrix(1, 1);
  auto test2 = S21Matrix(2, 2);
  ASSERT_ANY_THROW(test1.SumMatrix(test2));
}

TEST(SubMatrix, Test_1) {
  S21Matrix M;
  S21Matrix M2(2, 2);
  ASSERT_ANY_THROW(M.SubMatrix(M2));
}
TEST(SubMatrix, Test_2) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;
  auto test2 = test1;
  test1.SubMatrix(test2);
  ASSERT_EQ(test1(0, 0), 0);
}

TEST(SubMatrix, Test_3_notEq) {
  auto test1 = S21Matrix(1, 1);
  auto test2 = S21Matrix(2, 2);
  ASSERT_ANY_THROW(test1.SubMatrix(test2));
}

TEST(Test_MulNumber, test_1) {
  S21Matrix M(4, 4);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 5;
    }
  }
  M.MulNumber(10);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      ASSERT_DOUBLE_EQ(M(i, j), 50);
    }
  }
}

TEST(Test_MulNumber, Test_1) {
  S21Matrix M;
  M.SetRows(1);
  M.SetCols(1);
  M(0, 0) = 1;
  ASSERT_DOUBLE_EQ(M(0, 0), 1);
}

TEST(Test_MulNumber, Test_2) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 5;
  test1.MulNumber(3);
  ASSERT_EQ(test1(0, 0), 15);
}

TEST(Test_MulNumber, Test_3_noPtr) {
  auto test1 = S21Matrix();
  ASSERT_ANY_THROW(test1.MulNumber(3));
}

TEST(Test_MulMatrix, test_1) {
  S21Matrix M(2, 4);
  S21Matrix M2(4, 2);
  M.MulMatrix(M2);
  ASSERT_EQ(M.GetCols(), 2);
  ASSERT_EQ(M.GetRows(), 2);
}

TEST(Test_MulMatrix, test_2) {
  S21Matrix M(2, 4);
  S21Matrix M2(2, 4);
  ASSERT_ANY_THROW(M.MulMatrix(M2));
}

TEST(Test_MulMatrix, test_3) {
  S21Matrix M(3, 3);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = i + j;
    }
  }
  S21Matrix M2 = M;
  M.MulMatrix(M2);
  ASSERT_DOUBLE_EQ(M(0, 0), 5);
  ASSERT_DOUBLE_EQ(M(0, 1), 8);
  ASSERT_DOUBLE_EQ(M(0, 2), 11);

  ASSERT_DOUBLE_EQ(M(1, 0), 8);
  ASSERT_DOUBLE_EQ(M(1, 1), 14);
  ASSERT_DOUBLE_EQ(M(1, 2), 20);

  ASSERT_DOUBLE_EQ(M(2, 0), 11);
  ASSERT_DOUBLE_EQ(M(2, 1), 20);
  ASSERT_DOUBLE_EQ(M(2, 2), 29);
}

TEST(Test_MulMatrix, Test_4) {
  auto test1 = S21Matrix(3, 3);
  for (int i = 0; i < test1.GetRows(); i++) {
    for (int j = 0; j < test1.GetCols(); j++) {
      test1(i, j) = test1.GetRows() * i + j + 1;
    }
  }
  auto test2 = test1;
  test1.MulMatrix(test2);
  test2(0, 0) = 30;
  test2(0, 1) = 36;
  test2(0, 2) = 42;
  test2(1, 0) = 66;
  test2(1, 1) = 81;
  test2(1, 2) = 96;
  test2(2, 0) = 102;
  test2(2, 1) = 126;
  test2(2, 2) = 150;
  ASSERT_TRUE(test1 == test2);
}

TEST(Test_MulMatrix, Test_5_badPair) {
  auto test1 = S21Matrix(4, 1);
  auto test4 = S21Matrix(2, 3);
  ASSERT_ANY_THROW(test1.MulMatrix(test4));
}

TEST(Test_MulMatrix, Test_6_badMatrix) {
  auto test1 = S21Matrix(0, 0);
  auto test2 = S21Matrix(0, 0);
  ASSERT_ANY_THROW(test1.MulMatrix(test2));
}

TEST(Test_MulMatrix, Test_7_twoTimesMN) {
  auto test1 = S21Matrix(3, 3);
  for (int i = 0; i < test1.GetRows(); i++) {
    for (int j = 0; j < test1.GetCols(); j++) {
      test1(i, j) = test1.GetRows() * i + j + 1;
    }
  }
  auto test2 = test1;
  test1 = test1 * test2 * 2;
  test2(0, 0) = 30 * 2;
  test2(0, 1) = 36 * 2;
  test2(0, 2) = 42 * 2;
  test2(1, 0) = 66 * 2;
  test2(1, 1) = 81 * 2;
  test2(1, 2) = 96 * 2;
  test2(2, 0) = 102 * 2;
  test2(2, 1) = 126 * 2;
  test2(2, 2) = 150 * 2;
  ASSERT_TRUE(test1 == test2);
}

TEST(Test_Transpose, Test_1) {
  S21Matrix M(7, 2);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 4;
    }
  }
  S21Matrix M2 = M.Transpose();
  for (int i = 0; i < M.GetCols(); i++) {
    for (int j = 0; j < M.GetRows(); j++) {
      ASSERT_DOUBLE_EQ(M2(i, j), 4);
    }
  }
}

TEST(Test_Transpose, Test_2) {
  auto test1 = S21Matrix(3, 3);
  for (int i = 0; i < test1.GetRows(); i++) {
    for (int j = 0; j < test1.GetCols(); j++) {
      test1(i, j) = test1.GetRows() * i + j + 1;
    }
  }
  test1 = test1.Transpose();
  auto test2 = S21Matrix(3, 3);
  test2(0, 0) = 1;
  test2(0, 1) = 4;
  test2(0, 2) = 7;
  test2(1, 0) = 2;
  test2(1, 1) = 5;
  test2(1, 2) = 8;
  test2(2, 0) = 3;
  test2(2, 1) = 6;
  test2(2, 2) = 9;
  ASSERT_TRUE(test1 == test2);
}

TEST(Test_InverseMatrix, Test_1) {
  S21Matrix Matrix(3, 3);
  Matrix(0, 0) = 2;
  Matrix(0, 1) = 5;
  Matrix(0, 2) = 7;
  Matrix(1, 0) = 6;
  Matrix(1, 1) = 3;
  Matrix(1, 2) = 4;
  Matrix(2, 0) = 5;
  Matrix(2, 1) = -2;
  Matrix(2, 2) = -3;
  S21Matrix Matrix_Copy = Matrix.InverseMatrix();
  S21Matrix Matrix_2(3, 3);
  Matrix_2(0, 0) = 1;
  Matrix_2(0, 1) = -1;
  Matrix_2(0, 2) = 1;
  Matrix_2(1, 0) = -38;
  Matrix_2(1, 1) = 41;
  Matrix_2(1, 2) = -34;
  Matrix_2(2, 0) = 27;
  Matrix_2(2, 1) = -29;
  Matrix_2(2, 2) = 24;
  ASSERT_EQ(Matrix_Copy.EqMatrix(Matrix_2), SUCCESS);
}

TEST(Test_InverseMatrix, Test_2) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 2;
  test1(0, 1) = 5;
  test1(0, 2) = 7;
  test1(1, 0) = 6;
  test1(1, 1) = 3;
  test1(1, 2) = 4;
  test1(2, 0) = 5;
  test1(2, 1) = -2;
  test1(2, 2) = -3;
  test1 = test1.InverseMatrix();
  auto test2 = S21Matrix(3, 3);
  test2(0, 0) = 1;
  test2(0, 1) = -1;
  test2(0, 2) = 1;
  test2(1, 0) = -38;
  test2(1, 1) = 41;
  test2(1, 2) = -34;
  test2(2, 0) = 27;
  test2(2, 1) = -29;
  test2(2, 2) = 24;
  ASSERT_TRUE(test1 == test2);
}

TEST(Test_InverseMatrix, Test_3_zeroDet) {
  auto test1 = S21Matrix(2, 2);
  test1(0, 0) = 0;
  test1(0, 1) = 0;
  test1(1, 0) = 0;
  test1(1, 1) = 0;
  ASSERT_ANY_THROW(test1.InverseMatrix());
}

TEST(Test_InverseMatrix, Test_4_oneRow) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;
  auto test2 = S21Matrix(1, 1);
  test2(0, 0) = 1;
  ASSERT_TRUE(test1.InverseMatrix() == test2);
}

TEST(Test_InverseMatrix, Test_5) {
  S21Matrix M(3, 3);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 0;
    }
  }
  ASSERT_ANY_THROW(M.InverseMatrix());
}

TEST(Test_InverseMatrix, Test_6) {
  S21Matrix M(0, 0);
  ASSERT_ANY_THROW(M.InverseMatrix());
}

TEST(Test_CalcComplements, Test_1) {
  S21Matrix M(3, 3);
  M(0, 0) = 1;
  M(0, 1) = 2;
  M(0, 2) = 3;

  M(1, 0) = 0;
  M(1, 1) = 4;
  M(1, 2) = 2;

  M(2, 0) = 5;
  M(2, 1) = 2;
  M(2, 2) = 1;

  S21Matrix M2 = M.CalcComplements();
  ASSERT_DOUBLE_EQ(M2(0, 0), 0);
  ASSERT_DOUBLE_EQ(M2(0, 1), 10);
  ASSERT_DOUBLE_EQ(M2(0, 2), -20);

  ASSERT_DOUBLE_EQ(M2(1, 0), 4);
  ASSERT_DOUBLE_EQ(M2(1, 1), -14);
  ASSERT_DOUBLE_EQ(M2(1, 2), 8);

  ASSERT_DOUBLE_EQ(M2(2, 0), -8);
  ASSERT_DOUBLE_EQ(M2(2, 1), -2);
  ASSERT_DOUBLE_EQ(M2(2, 2), 4);
}

TEST(Test_CalcComplements, Test_2) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 0;
  test1(1, 1) = 4;
  test1(1, 2) = 2;
  test1(2, 0) = 5;
  test1(2, 1) = 2;
  test1(2, 2) = 1;
  test1 = test1.CalcComplements();
  auto test2 = S21Matrix(3, 3);
  test2(0, 0) = 0;
  test2(0, 1) = 10;
  test2(0, 2) = -20;
  test2(1, 0) = 4;
  test2(1, 1) = -14;
  test2(1, 2) = 8;
  test2(2, 0) = -8;
  test2(2, 1) = -2;
  test2(2, 2) = 4;
  ASSERT_TRUE(test1 == test2);
}

TEST(Test_CalcComplements, Test_3_notSquare) {
  auto test1 = S21Matrix(2, 3);
  ASSERT_ANY_THROW(test1.CalcComplements());
}

TEST(Test_Determinant, Test_1) {
  S21Matrix M(3, 3);
  M(0, 0) = 3;
  M(0, 1) = 2;
  M(0, 2) = 3;

  M(1, 0) = 4;
  M(1, 1) = 5;
  M(1, 2) = 6;

  M(2, 0) = 7;
  M(2, 1) = 8;
  M(2, 2) = 9;

  double res = M.Determinant();

  ASSERT_NEAR(res, -6, EPS);
}

TEST(Test_Determinant, Test_2) {
  S21Matrix M(2, 3);
  M(0, 0) = 8;
  M(0, 1) = 800;
  M(0, 2) = 5;

  M(1, 0) = 5;
  M(1, 1) = 5;
  M(1, 2) = 3;

  ASSERT_ANY_THROW(M.Determinant());
}

TEST(Test_Determinant, Test_3) {
  S21Matrix M(2, 2);
  M(0, 0) = 1;
  M(0, 1) = 2;

  M(1, 0) = 4;
  M(1, 1) = 5;

  double res = M.Determinant();
  ASSERT_NEAR(res, -3.0, EPS);
}

TEST(Test_Determinant, Test_4) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 0;
  test1(1, 1) = 4;
  test1(1, 2) = 2;
  test1(2, 0) = 5;
  test1(2, 1) = 2;
  test1(2, 2) = 1;
  ASSERT_DOUBLE_EQ(test1.Determinant(), -40);
}

TEST(Test_Determinant, Test_5_notSquare) {
  auto test1 = S21Matrix(1, 2);
  ASSERT_ANY_THROW(test1.Determinant());
}

TEST(Test_Operator_assignment_move, test_1) {
  S21Matrix M(4, 4);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 38.456;
    }
  }
  S21Matrix M2;
  M2 = std::move(M);
  for (int i = 0; i < M2.GetRows(); i++) {
    for (int j = 0; j < M2.GetCols(); j++) {
      ASSERT_DOUBLE_EQ(M2(i, j), 38.456);
    }
  }
  ASSERT_EQ(M.GetRows(), 0);
  ASSERT_EQ(M.GetCols(), 0);
}

TEST(Test_Operator_brackets, test_1) {
  S21Matrix M(4, 4);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 38;
    }
  }
  ASSERT_DOUBLE_EQ(M(2, 2), 38);
}

TEST(Test_Operator_Sum, test_1) {
  S21Matrix M(6, 6);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 10;
    }
  }
  S21Matrix M2 = M;
  S21Matrix M3 = M2 + M;
  for (int i = 0; i < M3.GetRows(); i++) {
    for (int j = 0; j < M3.GetCols(); j++) {
      ASSERT_EQ(M3(i, j), 20);
    }
  }
}

TEST(Test_Operator_Sub, test_1) {
  S21Matrix M(6, 6);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 32.666554;
    }
  }
  S21Matrix M2 = M;
  S21Matrix M3 = M - M2;
  for (int i = 0; i < M2.GetRows(); i++) {
    for (int j = 0; j < M2.GetCols(); j++) {
      ASSERT_EQ(M3(i, j), 0);
    }
  }
}

TEST(Test_Operator_MulMatrix, test_1) {
  S21Matrix M(4, 5);
  S21Matrix M2(4, 5);
  ASSERT_ANY_THROW(M * M2);
}

TEST(Test_Operator_EqMatrix, test_1) {
  S21Matrix M(3, 3);
  S21Matrix M2(2, 2);

  ASSERT_EQ(M == M2, FAILURE);
}

TEST(Test_Operator_MulNumber, test_1) {
  S21Matrix M(5, 5);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 38;
    }
  }
  S21Matrix M3 = M * 9;
  for (int i = 0; i < M3.GetRows(); i++) {
    for (int j = 0; j < M3.GetCols(); j++) {
      ASSERT_DOUBLE_EQ(M3(i, j), 342);
    }
  }
}

TEST(Test_Operator_SumMatrix_Assignment, test_1) {
  S21Matrix M(3, 3);
  S21Matrix M2(3, 4);

  ASSERT_ANY_THROW(M += M2);
}

TEST(Test_Operator_SubMatrix_Assignment, test_1) {
  S21Matrix M(3, 3);
  S21Matrix M2(3, 4);

  ASSERT_ANY_THROW(M -= M2);
}

TEST(Test_Operator_MulNumber_Assignment, test_1) {
  S21Matrix M(3, 3);
  M(0, 0) = 1;
  M(0, 1) = 2;
  M(0, 2) = 3;
  M(1, 0) = 1;
  M(1, 1) = 2;
  M(1, 2) = 3;
  M(2, 0) = 1;
  M(2, 1) = 2;
  M(2, 2) = 3;
  M *= 2;
  S21Matrix M1(3, 3);
  M1(0, 0) = 1 * 2;
  M1(0, 1) = 2 * 2;
  M1(0, 2) = 3 * 2;
  M1(1, 0) = 1 * 2;
  M1(1, 1) = 2 * 2;
  M1(1, 2) = 3 * 2;
  M1(2, 0) = 1 * 2;
  M1(2, 1) = 2 * 2;
  M1(2, 2) = 3 * 2;
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      ASSERT_DOUBLE_EQ(M(i, j), M1(i, j));
    }
  }
}

TEST(Test_Operator_MulMatrix_Assignment, test_1) {
  S21Matrix M(4, 5);
  S21Matrix M2(4, 5);

  ASSERT_ANY_THROW(M *= M2);
}

TEST(Test_Operator_MulMatrix_Assignment, test_2) {
  S21Matrix M(2, 8);
  S21Matrix M2;
  ASSERT_ANY_THROW(M *= M2);
  ASSERT_ANY_THROW(M2 *= M);
}

TEST(Test_SetRows, Test_1) {
  S21Matrix M(5, 5);
  ASSERT_ANY_THROW(M.SetRows(0));
}

TEST(Test_SetRows, Test_2) {
  S21Matrix M(1, 1);
  M(0, 0) = 12;
  M.SetRows(3);
  M(1, 0) = 7;
  S21Matrix M2(3, 1);
  M2(0, 0) = 12;
  M2(1, 0) = 7;
  ASSERT_TRUE(M == M2);
}

TEST(Test_SetCols, test_1) {
  S21Matrix M(5, 5);
  ASSERT_ANY_THROW(M.SetCols(0));
}

TEST(Test_SetCols, Test_2) {
  S21Matrix M(1, 1);
  M(0, 0) = 12;
  M.SetCols(3);
  M(0, 2) = 7;
  S21Matrix M2(1, 3);
  M2(0, 0) = 12;
  M2(0, 2) = 7;
  ASSERT_TRUE(M == M2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
