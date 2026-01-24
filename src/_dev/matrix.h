// #pragma once
// #include <vector>
// #include <stdexcept>
// #include "cell.h"

// /*
// Matrix<Type> name(num_cols, num_rows)
// name.at(cell) = Type object //setting example

// */

// // add the abilit to add a godot image and then treat it as a matrix
// //add it so i can do matrix(x,y) or matrix(cell)

// template <typename T> class Matrix {
// private:
//     size_t cols;
//     size_t rows;
//     std::vector<T> data;
// public:
//     Matrix(size_t c, size_t r): cols(c), rows(r), data(c*r) {} // fills data with typeT obj()
//     T& at(size_t idx) const {return data.at(idx);} //assumes idx is valid
//     T& at(const Cell& cell) const {
//         // assumes cell is valid
//         size_t idx = cell.get_rowwise_idx(cols);
//         return data.at(idx);}
//     const T& at(const Cell& cell) const { // this is needed so I can define a const memeber from a matrix
//         // assumes cell is valid
//         size_t idx = cell.get_rowwise_idx(cols);
//         return data.at(idx);}
// };