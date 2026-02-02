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
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "cell.hpp"

using namespace godot;

template <typename T> class Matrix {
    std::vector<T> data;
public:
    int cols, rows;
    constexpr Matrix(): Matrix(0,0) {}
    constexpr Matrix(int c, int r): cols(c), rows(r), data(c*r) {} //data filled with T()
    constexpr Matrix(int c, int r, std::vector<T> flat_matrix): cols(c), rows(r), data(flat_matrix) {}
    constexpr Matrix(std::vector<std::vector<T>> matrix): cols(matrix[0].size()), rows(matrix.size()), data(matrix[0].size()*matrix.size()) {
        for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            data[r * c + c] = matrix[r][c];
        }}
    }
    T& at(const Cell cell) { return data.at(cell.to_idx(cols)); } 
    const T& at(const Cell cell) const { return data.at(cell.to_idx(cols)); } 
    void display_full_as_int() const {
        for (int r = 0; r < rows; r++) {
            String line = "[";
            for (int c = 0; c < cols; c++) {
                Cell cell = Cell(c, r);
                line += vformat("%d", static_cast<int>(at(cell)));
                if (c < cols - 1) {line += " ";}
            }
            line += "]"; 
            UtilityFunctions::print(line); // I would love to use print_line here but I am unable.
        }
    }
};
