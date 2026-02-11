#pragma once
#include <vector>
#include <unordered_set> 
#include <godot_cpp/classes/image.hpp>
#include "cell.hpp"
#include "terrain_type.hpp"
#include "terrain_mod.hpp"
#include "direction.hpp"
#include "speed.hpp"
#include "image_matrix.hpp"

using namespace godot;

template <typename T> struct Matrix {
private:
    void set_data_from_copy(const ImageMatrix<TT>& mat) {
        std::vector<TT> new_data(mat.cols * mat.rows);
        const PackedByteArray bytes = mat.copy_bytes();
        const int num_bytes = bytes.size();
        for (int i = 0; i < num_bytes; i++) {
            new_data[i] = static_cast<TT>(bytes[i]);}
        data = new_data;
    }

    void set_data_from_copy(const ImageMatrix<TM>& mat) {
        std::vector<TM> new_data(mat.cols * mat.rows);
        const PackedByteArray bytes = mat.copy_bytes();
        const int num_bytes = bytes.size();
        for (int i = 0; i < num_bytes; i++) {
            new_data[i] = static_cast<TM>(bytes[i]);}
        data = new_data;
    }

    void set_data_from_copy(const ImageMatrix<Dir>& mat) {
        std::vector<Dir> new_data(mat.cols * mat.rows);
        const PackedByteArray bytes = mat.copy_bytes();
        const int num_bytes = bytes.size();
        for (int i = 0; i < num_bytes; i++) {
            new_data[i] = static_cast<Dir>(bytes[i]);}
        data = new_data;
    }

    void set_data_from_copy(const ImageMatrix<MPH>& mat, int sec_per_step, int feet_per_cell) {
        std::vector<Speed> new_data(mat.cols * mat.rows);
        const PackedByteArray bytes = mat.copy_bytes();
        const int num_bytes = bytes.size();
        for (int i = 0; i < num_bytes; i++) {
            new_data[i] = Speed(static_cast<MPH>(bytes[i]), sec_per_step, feet_per_cell);}
        data = new_data;
    }

    /*~300 ms faster than from_copy*/
    
    void set_data(const ImageMatrix<TT>& mat) {
        std::vector<TT> new_data(mat.cols * mat.rows);
        const uint8_t* bytes = mat.bytes_ptr();
        const int num_bytes = mat.num_bytes();
        for (int i = 0; i < num_bytes; i++) {
            new_data[i] = static_cast<TT>(bytes[i]);
        }
        data = new_data;
    }

    void set_data(const ImageMatrix<TM>& mat) {
        std::vector<TM> new_data(mat.cols * mat.rows);
        const uint8_t* bytes = mat.bytes_ptr();
        const int num_bytes = mat.num_bytes();
        for (int i = 0; i < num_bytes; i++) {
            new_data[i] = static_cast<TM>(bytes[i]);
        }
        data = new_data;
    }

    void set_data(const ImageMatrix<Dir>& mat) {
        std::vector<Dir> new_data(mat.cols * mat.rows);
        const uint8_t* bytes = mat.bytes_ptr();
        const int num_bytes = mat.num_bytes();
        for (int i = 0; i < num_bytes; i++) {
            new_data[i] = static_cast<Dir>(bytes[i]);
        }
        data = new_data;
    }

    void set_data(const ImageMatrix<MPH>& mat, int sec_per_step, int feet_per_cell) {
        std::vector<Speed> new_data(mat.cols * mat.rows);
        const uint8_t* bytes = mat.bytes_ptr();
        const int num_bytes = mat.num_bytes();
        for (int i = 0; i < num_bytes; i++) {
            new_data[i] = Speed(static_cast<MPH>(bytes[i]), sec_per_step, feet_per_cell);
        }
        data = new_data;
    }

public:
    std::vector<T> data;
    int cols, rows;

    Matrix(): 
        Matrix(0,0) {}

    Matrix(int c, int r, const T& default_val = T()): 
        cols(c), rows(r), data(c*r, default_val) {} 

    Matrix(int c, int r, const std::vector<T>& flat_matrix): 
        cols(c), rows(r), data(flat_matrix) {}

    Matrix(const ImageMatrix<TT>& tt): 
        cols(tt.cols), rows(tt.rows), 
        data(tt.cols * tt.rows) {
        set_data(tt);
    }

    Matrix(const ImageMatrix<TM>& tm): 
        cols(tm.cols), rows(tm.rows), 
        data(tm.cols * tm.rows) {
        set_data(tm);
    }

    Matrix(const ImageMatrix<Dir>& dir): 
        cols(dir.cols), rows(dir.rows), 
        data(dir.cols * dir.rows) {
        set_data(dir);
    }
    
    Matrix(const ImageMatrix<MPH>& mph, int sec_per_step, int feet_per_cell): 
        cols(mph.cols), rows(mph.rows), 
        data(mph.cols * mph.rows) {
        set_data(mph, sec_per_step, feet_per_cell);
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

