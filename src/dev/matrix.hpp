#pragma once
#include <vector>
#include <unordered_set> 
#include <stdexcept>
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
    void set_tt_from_image_matrix(const ImageMatrix<TT>& tt) {
        //must be r8
        std::vector<TT> tt_data(tt.cols * tt.rows);
        PackedByteArray bytes = tt.get_bytes();
        for (int i = 0; i < bytes.size(); i++) {
            tt_data[i] = static_cast<TT>(bytes[i]);}
        data = tt_data;
    }

    void set_tm_from_image_matrix(const ImageMatrix<TM>& tm) {
        //must be r8
        std::vector<TM> tm_data(tm.cols * tm.rows);
        PackedByteArray bytes = tm.get_bytes();
        for (int i = 0; i < bytes.size(); i++) {
            tm_data[i] = static_cast<TM>(bytes[i]);}
        data = tm_data;
    }

    void set_dir_from_image_matrix(const ImageMatrix<Dir>& dir) {
        //must be r8
        std::vector<Dir> dir_data(dir.cols * dir.rows);
        PackedByteArray bytes = dir.get_bytes();
        for (int i = 0; i < bytes.size(); i++) {
            dir_data[i] = static_cast<Dir>(bytes[i]);}
        data = dir_data;
    }

    void set_speed_from_image_matrix(const ImageMatrix<MPH>& mph, int sec_per_step, int feet_per_cell) {
        //must be r8
        std::vector<Speed> speed_data(mph.cols * mph.rows);
        PackedByteArray bytes = mph.get_bytes();
        for (int i = 0; i < bytes.size(); i++) {
            speed_data[i] = Speed(static_cast<MPH>(bytes[i]), sec_per_step, feet_per_cell);}
        data = speed_data;
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

