#include <iostream>
#include "simple_matrix.hpp"

// implement SimpleMatrix here

SimpleMatrix::SimpleMatrix(std::size_t nrows, std::size_t ncols) {} //Default constructor

SimpleMatrix::SimpleMatrix(std::initializer_list<std::initializer_list<double>> data) { //Constructor with initializer_list
    for (auto & row : data) {
        data_.push_back(row);
    }
}

SimpleMatrix::SimpleMatrix(const SimpleMatrix &other_mat):data_(other_mat.data_) { //Copy constructor
}

SimpleMatrix::SimpleMatrix(SimpleMatrix &&other_mat):data_(other_mat.data_){ //Move constructor
    other_mat.data_.clear();
}


SimpleMatrix &SimpleMatrix::operator=(const SimpleMatrix &other_mat) { //Copy assignment
    if (this != &other_mat){
        data_ = other_mat.data_;
    }
    return *this;
}

SimpleMatrix &SimpleMatrix::operator=(SimpleMatrix &&other_mat) { //Move assignment
    if (this != &other_mat){
        std::swap(data_, other_mat.data_);
    }
    return *this;
}

std::size_t SimpleMatrix::nrows() const {
    return data_.size();
}

std::size_t SimpleMatrix::ncols() const {
    return data_[0].size();
}

double &SimpleMatrix::operator()(std::size_t i, std::size_t j) {
    return data_[i][j];
}

double SimpleMatrix::operator()(std::size_t i, std::size_t j) const {
    if (i > nrows() || j > ncols()) throw std::out_of_range("Index i and j must not exceed data row and column size respectively.");
    return data_[i][j];
}
