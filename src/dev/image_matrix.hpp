/*
@brief: gives a type to the data inside an Image.
*/
#pragma once
#include <godot_cpp/classes/image.hpp>
// #include 

using namespace godot;

template <typename T> struct ImageMatrix {
    Ref<Image> image;
    int cols = 0;
    int rows = 0;
    ImageMatrix() {};
    explicit ImageMatrix(const Ref<Image> img): cols(img->get_width()), rows(img->get_height()), image(img) {}
    PackedByteArray get_bytes() const { return image->get_data(); } //copies the image data. change name to copy_bytes

    // static Matrix< to_matrix()
};


