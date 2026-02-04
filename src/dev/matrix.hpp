#pragma once
#include <vector>
#include <unordered_set> 
#include <stdexcept>
#include <godot_cpp/classes/image.hpp>
// #include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "cell.hpp"
#include "speed.hpp"
#include "terrain_type.hpp"
#include "terrain_mod.hpp"
#include "direction.hpp"
#include "image_matrix.hpp"

using namespace godot;

template <typename T> struct Matrix {
private:
    void set_tt_from_image_matrix(const ImageMatrix<TT>& tt) {
        std::vector<TT> tt_data(tt.cols * tt.rows);
        PackedByteArray bytes = tt.get_bytes();
        for (int i = 0; i < bytes.size(); i++) {
            tt_data[i] = static_cast<TT>(bytes[i]);}
        data = tt_data;
    }

    void set_tm_from_image_matrix(const ImageMatrix<TM>& tm) {
        std::vector<TM> tm_data(tm.cols * tm.rows);
        PackedByteArray bytes = tm.get_bytes();
        for (int i = 0; i < bytes.size(); i++) {
            tm_data[i] = static_cast<TM>(bytes[i]);}
        data = tm_data;
    }

    void set_dir_from_image_matrix(const ImageMatrix<Dir>& dir) {
        std::vector<Dir> dir_data(dir.cols * dir.rows);
        PackedByteArray bytes = dir.get_bytes();
        for (int i = 0; i < bytes.size(); i++) {
            dir_data[i] = static_cast<Dir>(bytes[i]);}
        data = dir_data;
    }

    void set_speed_from_image_matrix(const ImageMatrix<MPH>& mph, int sec_per_step, int feet_per_cell) {
        std::vector<Speed> speed_data(mph.cols * mph.rows);
        PackedByteArray bytes = mph.get_bytes();
        for (int i = 0; i < bytes.size(); i++) {
            speed_data[i] = Speed(bytes[i], sec_per_step, feet_per_cell);}
        data = speed_data;
    }

public:
    std::vector<T> data;
    int cols, rows;

    constexpr Matrix(): 
        Matrix(0,0) {}

    constexpr Matrix(int c, int r): 
        cols(c), rows(r), data(c*r) {} //data filled with T()

    constexpr Matrix(int c, int r, std::vector<T> flat_matrix): 
        cols(c), rows(r), data(flat_matrix) {}

    Matrix(const ImageMatrix<TT>& tt): 
        cols(tt.cols), rows(tt.rows), 
        data(tt.cols * tt.rows) {
        set_tt_from_image_matrix(tt);
    }

    Matrix(const ImageMatrix<TM>& tm): 
        cols(tm.cols), rows(tm.rows), 
        data(tm.cols * tm.rows) {
        set_tm_from_image_matrix(tm);
    }

    Matrix(const ImageMatrix<Dir>& dir): 
        cols(dir.cols), rows(dir.rows), 
        data(dir.cols * dir.rows) {
        set_dir_from_image_matrix(dir);
    }
    
    Matrix(const ImageMatrix<MPH>& mph, int sec_per_step, int feet_per_cell): 
        cols(mph.cols), rows(mph.rows), 
        data(mph.cols * mph.rows) {
        set_speed_from_image_matrix(mph, sec_per_step, feet_per_cell);
    } 
        
    T& at(int c, int r) { 
        return data.at(r*cols + c); 
    } 

    const T& at(int c, int r) const { 
        return data.at(r*cols + c); 
    } 

    T& at(const Cell cell) { 
        return data.at(cell.to_idx(cols)); 
    } 

    const T& at(const Cell cell) const { 
        return data.at(cell.to_idx(cols)); 
    } 

    const std::unordered_set<int> to_unique_ints() const {
        //converts the T to an int and adds it to a set
        std::unordered_set<int> unique_ints;
        for (const T& item : data) { unique_ints.insert(static_cast<int>(item)); }
        return unique_ints;
    }

    int count_unique_ints() const { 
        return to_unique_ints().size();
    }
    bool operator==(const Matrix<T> other) const { return data == other.data; }
    bool operator!=(const Matrix<T> other) const { return data != other.data; }
};





// /*
// @example
// ===============
// Matrix<int> mat(10, 10);
// const Matrix<int>& const_mat = mat;

// mat.at(Cell(5, 5)) = 42;           // OK: calls non-const version, returns T&
// int val = const_mat.at(Cell(5, 5)); // OK: calls const version, returns const T&
// const_mat.at(Cell(5, 5)) = 99;      // ERROR: can't modify through const T&
// ---------------
// */
// #pragma once
// #include <vector>
// #include <unordered_set> 
// #include <stdexcept>
// #include <godot_cpp/classes/image.hpp>
// #include <godot_cpp/variant/string.hpp>
// #include <godot_cpp/variant/utility_functions.hpp>
// #include "cell.hpp"
// #include "speed.hpp"
// #include "terrain_type.hpp"
// #include "terrain_mod.hpp"
// #include "direction.hpp"
// #include "image_matrix.hpp"

// using namespace godot;

// template <typename T> struct Matrix {
// private:
//     // Matrix(const Ref<Image> data_image) {
//     //     if (T::IMAGE_FORMAT != Image::FORMAT_R8) {
//     //         throw std::invalid_argument("Matrix T::IMAGE_FORMAT is not R8");}
//     //     if (data_image->get_format() != T::IMAGE_FORMAT) {
//     //         throw std::invalid_argument("Given data_image has incorrect image format");}
//     //     Matrix<T> result(data_image->get_width(), data_image->get_height());
//     //     PackedByteArray byte_array = data_image->get_data();
//     //     for (int i = 0; i < byte_array.size(); i++) {
//     //         result.data[i] = static_cast<T>(byte_array[i]);}
//     //     return result;
//     // }


//     static Matrix<Dir> img_matrix_dir_to_matrix_dir(const ImageMatrix<Dir>& dir) {
//         Matrix<Dir> result(dir.cols, dir.rows);
//         PackedByteArray bytes = dir.get_bytes();
//         for (int i = 0; i < bytes.size(); i++) {
//             result.data[i] = Speed(bytes[i], sec_per_step, feet_per_cell);}
//         return result;
//     }

//     static Matrix<Speed> img_matrix_mph_to_matrix_speed(const ImageMatrix<MPH>& mph, int sec_per_step, int feet_per_cell) {
//         Matrix<Speed> result(mph.cols, mph.rows);
//         PackedByteArray bytes = mph.get_bytes();
//         for (int i = 0; i < bytes.size(); i++) {
//             result.data[i] = Speed(bytes[i], sec_per_step, feet_per_cell);}
//         return result;
//     }

//         /*
//     Copy from Image
//     */

//     // static Matrix<TT> create_tt_matrix(const Ref<Image> data_image) {
//     //     return Matrix<TT>(data_image);
//     // }

//     // static Matrix<TM> create_tm_matrix(const Ref<Image> data_image) {
//     //     return Matrix<TM>(data_image);
//     // }

//     // static Matrix<Dir> create_dir_matrix(const Ref<Image> data_image) {
//     //     return Matrix<Direction>(data_image);
//     // }

//     // static Matrix<Speed> create_speed_matrix(const Ref<Image> mph_image, int sec_per_step, int feet_per_cell) {
//     //     if (mph_image->get_format() != Speed::IMAGE_FORMAT) {
//     //         throw std::invalid_argument("Given mph_image has incorrect image format");}
//     //     Matrix<Speed> result(mph_image->get_width(), mph_image->get_height());
//     //     PackedByteArray byte_array = mph_image->get_data();
//     //     for (int i = 0; i < byte_array.size(); i++) {
//     //         result.data[i] = Speed(byte_array[i], sec_per_step, feet_per_cell);}
//     //     return result;
//     // }

// public:
//     std::vector<T> data;
//     int cols, rows;

//     constexpr Matrix(): 
//         Matrix(0,0) {}

//     constexpr Matrix(int c, int r): 
//         cols(c), rows(r), data(c*r) {} //data filled with T()

//     constexpr Matrix(int c, int r, std::vector<T> flat_matrix): 
//         cols(c), rows(r), data(flat_matrix) {}
    
//     Matrix(const ImageMatrix<MPH>& mph, int sec_per_step, int feet_per_cell): 
//         cols(mph.cols), rows(mph.rows), data(mph.cols * mph.rows) {
//         data(img_matrix_mph_to_matrix_speed(mph, sec_per_step, feet_per_cell));
//     } 
        
//     T& at(int c, int r) { 
//         return data.at(r*cols + c); 
//     } 

//     const T& at(int c, int r) const { 
//         return data.at(r*cols + c); 
//     } 

//     T& at(const Cell cell) { 
//         return data.at(cell.to_idx(cols)); 
//     } 

//     const T& at(const Cell cell) const { 
//         return data.at(cell.to_idx(cols)); 
//     } 

//     const std::unordered_set<int> to_unique_ints() const {
//         //converts the T to an int and adds it to a set
//         std::unordered_set<int> unique_ints;
//         for (const T& item : data) { unique_ints.insert(static_cast<int>(item)); }
//         return unique_ints;
//     }

//     int count_unique_ints() const { 
//         return to_unique_ints().size();
//     }

//     void display_full_as_int() const {
//         for (int r = 0; r < rows; r++) {
//             String line = "[";
//             for (int c = 0; c < cols; c++) {
//                 Cell cell = Cell(c, r);
//                 line += vformat("%d", static_cast<int>(at(cell)));
//                 if (c < cols - 1) {line += " ";}
//             }
//             line += "]"; 
//             UtilityFunctions::print(line); // I would love to use print_line here but I am unable.
//         }
//     }


// };
