#ifndef MATRIX_H_
#define MATRIX_H_

#include <concepts>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <utility>
#include <vector>

template<class T>
concept is_multiplicable = requires(T a, T b) {
  { a* b } noexcept -> std::same_as<T>;
};

template<class T>
concept is_additive = requires(T a, T b) {
  { a + b } noexcept -> std::same_as<T>;
  { a += b } noexcept;
};

class invalid_dimensions_error: public std::exception {};

template<typename T>
  requires is_additive<T> && is_multiplicable<T> && std::default_initializable<T>
class Matrix {
  T* values;
  std::size_t n;

  Matrix<T>(size_t size):
      n(size) { values = new T[n * n](); }

public:
  Matrix(std::size_t size, T value):
      Matrix<T>(size) {
    for (std::size_t i = 0; i < n; ++i) {
      values[i * (n + 1)] = value; //TODO
    }
  }

  Matrix(std::vector<T> values):
      Matrix<T>(values.size()) {
    for (std::size_t i = 0; i < n; ++i) {
      this->values[i * (n + 1)] = values[i];
    }
  }

  Matrix(const Matrix<T>& other):
      Matrix<T>(other.n) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        (*this)[i][j] = other[i][j];
      }
    }
  }

  Matrix(Matrix<T>&& other):
      n(other.n) {
    values       = other.values;
    other.values = nullptr;
  }

  Matrix<T>& operator=(const Matrix<T>& other) {
    Matrix<T> copy(other);
    std::swap(*this, copy);
    return *this;
  }

  Matrix<T>& operator=(Matrix<T>&& other) {
    n = other.n;
    std::swap(values, other.values);
  }

  ~Matrix() {
    delete[] values;
  }

  Matrix<T> operator+(const Matrix<T>& other) const {
    if (n != other.n)
      throw invalid_dimensions_error();

    Matrix result = Matrix<T>(n);
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        result[i][j] = (*this)[i][j] + other[i][j];
      }
    }
    return result;
  }

  Matrix<T>& operator+=(const Matrix<T>& other) {
    if (n != other.n)
      throw std::exception();

    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        (*this)[i][j] += other[i][j];
      }
    }
    return *this;
  }

  Matrix<T> operator*(const Matrix<T>& other) const {
    if (n != other.n)
      throw std::exception();

    Matrix<T> result = Matrix<T>(n);

    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        T sum = T();
        for (size_t k = 0; k < n; k++) {
          sum += (*this)[i][k] * other[k][j];
        }
        result[i][j] = sum;
      }
    }

    return result;
  }

  Matrix<T>& operator*=(const Matrix<T>& other) {
    Matrix<T> result = *this * other;
    *this            = std::move(result);
    return *this;
  }

  Matrix<T>& operator*=(T scalar) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        (*this)[i][j] = (*this)[i][j] * scalar;
      }
    }
    return *this;
  }

  Matrix<T> operator*(T scalar) const {
    Matrix<T> result = *this;
    result *= scalar;
    return result;
  }

  bool operator==(const Matrix<T>& other) const {
    if (n != other.n)
      return false;

    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        if ((*this)[i][j] != other[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Matrix<T>& other) const {
    return !((*this) == other);
  }

  explicit operator T() const {
    T sum = T();

    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        sum += (*this)[i][j];
      }
    }

    return sum;
  }

  class MatrixView {
    T* values;
    size_t n;
    friend Matrix<T>;

    MatrixView(T* v, size_t s):
        values(v), n(s) {}

  public:
    T& operator[](std::size_t i) const {
      if (i >= n)
        throw std::out_of_range("Matrix index out of bounds");
      return values[i];
    }
  };

  const MatrixView operator[](std::size_t i) const {
    if (i >= n)
      throw std::out_of_range("Matrix index out of bounds");
    return MatrixView(&values[i * n]);
  }
};

#endif
