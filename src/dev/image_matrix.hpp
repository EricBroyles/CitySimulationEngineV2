/*
@brief: gives a type to the data inside an Image.
*/
#pragma once
#include <stdexcept>
#include <godot_cpp/classes/image.hpp>

using namespace godot;

template <typename T> struct ImageMatrix {
    Ref<Image> image;
    int cols = 0;
    int rows = 0;

    ImageMatrix() {};

    explicit ImageMatrix(const Ref<Image> img, const Image::Format assert_img_format): cols(img->get_width()), rows(img->get_height()), image(img) {
        if (img->get_format() != assert_img_format) {
            throw std::invalid_argument("The provided Images format does not match the assert img format. ");
        }
    }

    PackedByteArray copy_bytes() const { 
        return image->get_data(); 
    } 

    const uint8_t* bytes_ptr() const {
        if (image.is_null()) {
            throw std::runtime_error("Cannot get pointer from null image");
        }
        return image->ptr();
    }

    size_t num_bytes() const {
        return cols * rows * get_bytes_per_pixel();
    }

    int get_bytes_per_pixel() const {
        switch (image->get_format()) {
            case Image::FORMAT_R8: return 1;
            case Image::FORMAT_RGB8: return 3;
            case Image::FORMAT_RGBA8: return 4;
            default: throw std::runtime_error("Unsupported image format");
        }
    }
};


