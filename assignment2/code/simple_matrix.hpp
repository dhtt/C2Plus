#ifndef SIMPLE_MATRIX_HPP
#define SIMPLE_MATRIX_HPP

#include <vector>

class SimpleMatrix {
 public:
  // Thrown in case of invalid usage	 
  class Invalid {};

  SimpleMatrix(std::size_t nrows, std::size_t ncols);
  SimpleMatrix(std::initializer_list<std::initializer_list<double>> data);

  SimpleMatrix(const SimpleMatrix& other_mat);
  SimpleMatrix(SimpleMatrix&& other_mat);

  SimpleMatrix& operator=(const SimpleMatrix& other_mat);
  SimpleMatrix& operator=(SimpleMatrix&& other_mat);

  std::size_t nrows() const;
  std::size_t ncols() const;

  double& operator()(std::size_t i, std::size_t j);
  double operator()(std::size_t i, std::size_t j) const;

 private:
  std::vector<std::vector<double>> data_;
};

#endif  // SIMPLE_MATRIX_HPP
