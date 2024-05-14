#include "s21_matrix_oop.h"

// Вспомогательные функции
/**
 * @brief Валидация матриц this и other
 * @details Первичная проверка на валидность матриц для проведения операций
 * @param other одна из проверяемых матриц
 */
bool S21Matrix::CheckMatrix(const S21Matrix& other) const noexcept {
  bool res = s21::PASSED;
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    res = s21::FAILED;
  }
  if (rows_ < 1 || cols_ < 1 || other.rows_ < 1 || other.cols_ < 1) {
    res = s21::FAILED;
  }
  return res;
}

void S21Matrix::FreeMatrix() {
  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
}
/**
 * @brief Вспомогательная функция. Алокация памяти.
 * @details
 *       try{..} catch(..) {..}
 * необходим для выброса ошибки при провальной инициализации памяти
 * std::bad_allock(), а так же чисткой памяти в такой ситуации.
 */
void S21Matrix::AllocateMatrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    try {
      matrix_[i] = new double[cols_];
    } catch (...) {
      for (int j = 0; j < i; ++j) {
        delete[] matrix_[j];
      }
      delete[] matrix_;
      throw std::bad_alloc();
    }
  }
  FillWithZeroes();
}

void S21Matrix::FillWithZeroes() noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

// Конструкторы
/**
 * @brief Конструктор по умолчанию.
 * @details
 * Создание объекта S21Matrix с размерами [0 х 0].
 * Для присвоение значений используется Member Initializer List
 * или "MIL" - великая штука.
 * Метод не генерирует исключения, поэтому используем "Спецификатор
 * времени компиляции" noexcept - подсказываем компилятору ситуацию
 * описанную выше, тем самым уменьшается размер генерируемого файла
 * и ускоряется работа самой программы.
 */
S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

/**
 * @brief Конструктор параметизированный
 * @details
 * Присвоение переменных так же происходит в MIL.
 * Метод генерирует исключения, поэтому noexcept не используется
 * @param rows количество строк
 * @param cols количество столбцов
 *
 */
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::length_error("Matrix size must be greater than 0");
  }
  this->AllocateMatrix();
}
/**
 * @brief Конструктор копирования
 * @details
 * Фришим матрицу. присваиваем новые данные о размерах, заново аллоцируем
 * память и копируем с помощью memcpy.
 * @param other Матрица из которой копируем данные
 */
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  this->AllocateMatrix();
  for (int i = 0; i < rows_; i++) {
    memcpy(matrix_[i], other.matrix_[i], other.cols_ * sizeof(double));
  }
}
/**
 * @brief Конструктор переноса
 * @details
 * В MIL обновлаяем значения this из other и зануляем переменные объекта other
 * @param other
 */
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

// Базовые операции над матрицами
bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  int is_eq = s21::PASSED;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    is_eq = s21::FAILED;
  }
  if (is_eq == s21::PASSED) {
    for (int i = 0; i < rows_ && is_eq == true; i++) {
      for (int j = 0; j < cols_ && is_eq == true; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          is_eq = s21::FAILED;
        }
      }
    }
  }
  return is_eq;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matricex should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matricex should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (matrix_ == nullptr) {
    throw std::bad_weak_ptr();
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  bool matrix_status = this->CheckMatrix(other);
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Incorrect input, matricex should have format M1.cols_ = M2.rows_");
  } else if (matrix_status == s21::PASSED) {
    S21Matrix new_matrix(rows_, other.GetCols());
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        new_matrix.matrix_[i][j] = 0;
        for (int k = 0; k < other.rows_; k++) {
          new_matrix.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    *this = new_matrix;
  } else {
    throw std::out_of_range("Invalid matrix");
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix should have square format.");
  }
  double res = 1.0;
  S21Matrix temp_m{*this};
  int size = rows_;
  for (int i = 0; i < size; ++i) {
    int plot_ind = i;
    for (int j = i + 1; j < size; ++j) {
      if (std::abs(temp_m(j, i)) > std::abs(temp_m(plot_ind, i))) {
        plot_ind = j;
      }
    }
    if (std::abs(temp_m(plot_ind, i)) < 1e-7) {
      return 0.0;
    }
    temp_m.SwapRows(i, plot_ind);
    res *= temp_m(i, i);
    if (i != plot_ind) {
      res = -res;
    }
    for (int j = i + 1; j < size; ++j) {
      double coeff = temp_m(j, i) / temp_m(i, i);
      for (int k = i; k < size; ++k) {
        temp_m(j, k) -= temp_m(i, k) * coeff;
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcMinorMat(int i_ignore, int j_ignore) {
  S21Matrix res(rows_ - 1, cols_ - 1);
  int shift_row = 0;
  for (int i = 0; i < res.rows_; ++i) {
    if (i == i_ignore) {
      shift_row = 1;
    }
    int shift_col = 0;
    for (int j = 0; j < res.cols_; ++j) {
      if (j == j_ignore) {
        shift_col = 1;
      }
      res(i, j) = (*this)(i + shift_row, j + shift_col);
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix should have square format.");
  }
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < res.rows_; i++) {
    for (int j = 0; j < res.cols_; j++) {
      S21Matrix minor_matrix = CalcMinorMat(i, j);
      res(i, j) = minor_matrix.Determinant();

      if ((i + j) % 2 != 0) {
        res(i, j) = -res(i, j);
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (matrix_ == nullptr || cols_ < 1 || rows_ < 1) {
    throw std::out_of_range("Invalid matrix");
  }
  double det = 0;
  det = this->Determinant();
  if (det == 0) {
    throw std::invalid_argument("Determinant for this matrix is equal 0.");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res(0, 0) = 1 / det;
  } else {
    res = CalcComplements();
    res = res.Transpose();
    // res.MulNumber(1 / det);
    for (int i = 0; i < cols_; i++) {
      for (int j = 0; j < rows_; j++) {
        res.matrix_[i][j] /= det;
      }
    }
  }
  return res;
}

// Перегрузка операторов
double& S21Matrix::operator()(int row, int col) {
  double* ptr;
  ptr = &matrix_[row][col];
  return *ptr;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix sum = *this;
  sum += other;
  return sum;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix sub = *this;
  sub -= other;
  return sub;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix mul(*this);
  mul.MulMatrix(other);
  return mul;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix mul_num = *this;
  mul_num *= num;
  return mul_num;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  this->AllocateMatrix();

  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return EqMatrix(other);
}

// Accessors
const int& S21Matrix::GetRows() const noexcept { return this->rows_; }

const int& S21Matrix::GetCols() const noexcept { return this->cols_; }

// Mutators
void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::invalid_argument("Size of raws cannot be below 1");
  }
  S21Matrix tmp(rows, cols_);
  if (rows > rows_) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        if (i < rows_) {
          tmp.matrix_[i][j] = this->matrix_[i][j];
        } else {
          tmp.matrix_[i][j] = 0;
        }
      }
    }
  }
  *this = tmp;
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::invalid_argument("Size of raws cannot be below 1");
  }
  S21Matrix tmp(rows_, cols);
  if (cols > cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols; j++) {
        if (j < cols_)
          tmp.matrix_[i][j] = this->matrix_[i][j];
        else
          tmp.matrix_[i][j] = 0;
      }
    }
  }
  *this = tmp;
}

// Helper
void S21Matrix::SwapRows(int row1, int row2) noexcept {
  if (row1 != row2) {
    for (int i = 0; i < cols_; ++i) {
      std::swap((*this)(row1, i), (*this)(row2, i));
    }
  }
}

// Destructor
S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    this->FreeMatrix();
    this->matrix_ = nullptr;
    this->cols_ = 0;
    this->rows_ = 0;
  }
}
