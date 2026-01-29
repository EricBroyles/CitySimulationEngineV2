/*
@example
===============
Matrix<int> mat(10, 10);
const Matrix<int>& const_mat = mat;

mat.at(Cell(5, 5)) = 42;           // OK: calls non-const version, returns T&
int val = const_mat.at(Cell(5, 5)); // OK: calls const version, returns const T&
const_mat.at(Cell(5, 5)) = 99;      // ERROR: can't modify through const T&
---------------
*/
#pragma once
#include <vector>
#include "cell.hpp"

template <typename T> class Matrix {
    std::vector<T> data;
public:
    int cols, rows;
    constexpr Matrix(): Matrix(0,0) {}
    constexpr Matrix(int c, int r): cols(c), rows(r), data(c*r) {} //data filled with T()
    T& at(const Cell& cell) { return data.at(cell.to_idx(cols)); } //used with Matrix, can modify
    const T& at(const Cell& cell) const { return data.at(cell.to_idx(cols)); } //used with const Matrix, read only (returns a constant reference)
};
