/*
@brief: gives a type to the data inside an Image.
*/
#pragma once
#include <godot_cpp/classes/image.hpp>

using namespace godot;

template <typename T> struct ImageMatrix {
    Ref<Image> image;
    int cols = 0;
    int rows = 0;
    bool valid = false;

    ImageMatrix() = default;

    explicit ImageMatrix(const Ref<Image>& img) : image(img) {
        if (image.is_null()) { valid = false; return; }
        cols = image->get_width();
        rows = image->get_height();
        valid = true;
    }

    PackedByteArray get_bytes() const {
        if (image.is_null()) {
            return PackedByteArray(); 
        }
        return image->get_data();
    }
};


