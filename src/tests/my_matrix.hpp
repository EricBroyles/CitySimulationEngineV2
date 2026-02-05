#pragma once 
#include <godot_cpp/variant/string.hpp>
#include "../dev/matrix.hpp"

using namespace godot;

template <typename T> struct MyMatrix {

    static void display_full_as_int(const Matrix<T>& matrix) {
        for (int r = 0; r < matrix.rows; r++) {
            String line = "[";
            for (int c = 0; c < matrix.cols; c++) {
                Cell cell = Cell(c, r);
                line += vformat("%d", static_cast<int>(matrix.at(cell)));
                if (c < matrix.cols - 1) {line += " ";}
            }
            line += "]"; 
            print_line(line);
        }
    }
};
